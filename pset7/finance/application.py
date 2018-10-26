import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # Remember id
    ident = session["user_id"]

    # Info from data table and cash of user
    row = db.execute ("select * from users where id = :ii" , ii = ident)

    # Take info about stocks bought
    simbol = db.execute("SELECT symbol, price, SUM(shares) as total_shares FROM portfolio WHERE id = :ii GROUP BY symbol ORDER BY symbol",ii=ident)

    # If user has not bought stocks
    if not simbol:
        return render_template ("noshares.html",cash = row[0]["cash"])
    else:
        total = 0

        # Iterrate over each element in simbol
        for share in simbol:

            # Get symbol of each element
            symbol = share ["symbol"]

            # Lookup current price of stock symbol
            quote = lookup (symbol)

            # the current price
            share["quoteprice"] = quote["price"]

            # Total quote price of each stock with sum of shares of each stock
            total += quote["price"] * share ["total_shares"]

        # total plus the cash user has
        totl = total + row[0]["cash"]

        # render values
        return render_template ("index.html", symbol = simbol,cash = row[0]["cash"],total = totl)
    #return apology("TODO")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock."""
    if request.method == "POST":
        print("post buy execute")

        if not request.form.get("symbol"):
            return apology("must enter a stock symbol")
        elif not request.form.get("shares"):
            return apology("must enter number of shares")

        symbol = request.form.get("symbol")
        quote = lookup(symbol)

        if not quote:
            return apology("must enter valid stock symbol")

        user = db.execute("SELECT cash FROM users WHERE id=:userId;", userId=session["user_id"])
        userBalance = float(user[0]["cash"])
        totalCost = quote["price"]*int(request.form.get("shares"))
        if totalCost>userBalance:
            return apology("not enough funds for purchase")
        else:
            db.execute("INSERT INTO portfolio (symbol, shares, price, id) VALUES (:symbol, :shares, :price, :user_id);", symbol=symbol, shares=request.form.get("shares"), price=quote['price'], user_id=session["user_id"])
            db.execute("UPDATE users SET cash=cash-:cost WHERE id=:userId;", cost=totalCost, userId=session["user_id"])
            print("bought stocks")
        return redirect("/")
    else:
        return render_template("buy.html")

@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    row = db.execute("SELECT * FROM users WHERE id = :ide", ide = session["user_id"])

    simbol = db.execute("SELECT * FROM portfolio WHERE id = :ide",ide = session["user_id"])

    #if user has not bought any stock
    if not simbol:
        return render_template ("noshares.html",cash = row[0]["cash"])

    return render_template ("history.html", symbol = simbol)
    #return apology("TODO")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("Must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("Must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("Invalid username/password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure stock symbol is given
        if not request.form.get("symbol"):
            return apology("Enter stock symbol")

        symbol = request.form.get("symbol")
        quote = lookup(symbol)

        if quote:
            return render_template("quoted.html", company=quote["name"], symbol=quote["symbol"], price=usd(quote["price"]))
        else:
            return apology("Enter valid stock symbol")

    else:
        return render_template("quote.html")
    #return apology("TODO")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
       # User reached route via POST
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("Must provide username", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))

        # Check if username is already in the database
        if len(rows) != 0:
            return apology("Username already exists", 400)

        # Ensure that password was submitted
        if not request.form.get("password"):
            return apology("Must provide password", 400)

        # Ensure that password was entered again
        if not request.form.get("confirmation"):
            return apology("Enter password again", 400)

        # Ensure that passwords match
        if not request.form.get("password") == request.form.get("confirmation"):
            return apology("Passwords must match", 400)

        # Insert data in the database
        signup = db.execute("INSERT INTO users (username, hash) VALUES(:username, :hash_password)",
                            username = request.form.get("username"),
                            hash_password = generate_password_hash(request.form.get("password")))

        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":

        # Remember id
        ide = session["user_id"]

        # Get the symbol
        sym = request.form.get("symbol")
        if not sym:
            return apology ("Must enter the symbol")

        # Get number of stocks and take user's shares of that symbol
        sybl = db.execute ("select * from portfolio where id = :ii AND symbol = :sym", ii = ide, sym = sym)

        # if user has not bought any stock
        if not sybl:
            # go back to index page
            return redirect("/")

        while True:
            num = request.form.get("number")

            try:
                numb = float (num)
            except ValueError:
                return apology ("Enter valid number of sell stocks")
                continue
            else:
                break
        if numb is None or numb == '' or numb < 1 or numb > sybl[0]["shares"]:
            return apology ("Enter valid number of sell stocks")

        row = db.execute ("select * from users where id = :ii" , ii = ide)

        # Lookup and save dict quoted
        quoted = lookup(sym)

        # If symbol is invalid
        if not quoted:
            return apology ("Invalid stock")

        else:
            # Take price from dict quoted
            qtd = quoted["price"]

            # Multiply current price with number of stocks to determine total value of stocks sold
            prc = float(qtd)*numb

            # Add current price of stock to user cash
            db.execute("UPDATE users SET cash = :cash WHERE id = :ide",cash = row[0]["cash"] + prc, ide = ide)

            # =negative number of sale
            db.execute("INSERT INTO portfolio (id, symbol, price, shares, action, dtime) VALUES (:ide, :symbol, :price, :shares,'Sell', DateTime('now'))", ide = ide, symbol = sym, price = prc, shares = -numb)
            return redirect("/")
    else:
        return render_template("sell.html")

    #return apology("TODO")

@app.route("/addcash", methods=["GET", "POST"])
@login_required
def addcash():
    # add cash to user
    if request.method == "POST":
        # Take amount to be added
        while True:
            num = request.form.get("amount")
            try:
                numb = int (num)
            except ValueError:
                return apology ("Enter valid amount to add")
                continue
            else:
                break
        if numb is None or numb == '' or numb < 1:
            return apology ("Enter valid amount")
        else:
            # takes user cash
            row = db.execute ("select cash from users where id = :ii" , ii = session["user_id"])

            # Add the amount to users database
            db.execute("UPDATE users SET cash = :cash WHERE id = :ide",cash = row[0]["cash"] + numb, ide = session["user_id"])
        return redirect("/")

    else:
        return render_template("addcash.html")


def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)

# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)