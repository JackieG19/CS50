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
    #Remember id
    ide = session["user_id"]

    #Take all info from users data table and determine cash of user.
    row = db.execute ("select * from users where id = :ii" , ii = ide)

    #take info about shares user has bought
    simbol = db.execute("SELECT symbol, price, SUM(shares) as total_shares FROM portfolio WHERE id = :ii GROUP BY symbol ORDER BY symbol",ii=ide)

    #if user has not bought any sahres then display noshare html file.
    if not simbol:

    #Return user a message in html and his cash holdings.
        return render_template ("noshares.html",cash = row[0]["cash"])
    else:
        total = 0

        #Iterrate over each element in symb
        for share in simbol:

            #Get symbol of each element
            symbol = share ["symbol"]

            #Lookup current price of that specific symbol/sahre
            quote = lookup (symbol)

            #save each current price
            share["quoteprice"] = quote["price"]

            #Total equels fresh quote price of  each stock * sum of shares of each stock
            total += quote["price"] * share ["total_shares"]

        #grand is equel to total + the cash user has in his account
        grand = total + row[0]["cash"]

        #render values
        return render_template ("index.html", symbol = simbol,cash = row[0]["cash"],total = grand)
    #return apology("TODO")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":

        #take symbol from user
        symbl = request.form.get("symbol")
        if not symbl:
            return apology ("Enter the symbol")

        while True:
            #Number of shares to buy
            num = request.form.get("number")

            try:
                number = float (num)
            except ValueError:
                return apology ("Enter valid number of buy stocks")
                continue
            else:
                break
        if number is None or number == '' or number < 1:
            return apology ("Enter valid number of buy stocks")


        #Lookup and save dict in quoted
        quoted = lookup(symbl)

        #If symbol is invalid return apology
        if not quoted:
            return apology ("Invalid stock")
        else:
            #qtd saves price of share
            qtd = quoted["price"]

            #price of single share * Number of sahres required to buy
            prc = float(qtd) * number

            #remember session id
            ide = session["user_id"]

            csh = db.execute("SELECT * FROM users WHERE id = :ide", ide = ide)

            #Only go forward if user have enough
            if prc <= csh[0]["cash"]:
                db.execute("INSERT INTO portfolio (id, symbol,price,shares,action,dtime) VALUES (:ide, :symbol, :price, :shares,'Buy', DateTime('now'))", ide = ide,symbol = symbl, price = prc, shares = number)
                db.execute("UPDATE users SET cash = :cash WHERE id = :ide",cash = csh[0]["cash"] - prc, ide = ide)
                return render_template("buy.html")
            else:
                return apology ("Not enough cash to buy stocks")
    else:
        return render_template("buy.html")

    #return apology("TODO")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    row = db.execute("SELECT * FROM users WHERE id = :ide", ide = session["user_id"])

    #Select all from portfolio
    simbol = db.execute("SELECT * FROM portfolio WHERE id = :ide",ide = session["user_id"])

    #if user has not bought any sahres then display noshare html file.
    if not simbol:

    #Return user a message in html and his cash holdings.
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

        # Ensure that password was entered twice
        if not request.form.get("confirmation"):
            return apology("Enter password again", 400)

        # Ensure that passwords match
        if not request.form.get("password") == request.form.get("confirmation"):
            return apology("Passwords must match", 400)

        # Insert data into database
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

        #Remember id
        ide = session["user_id"]

        #Get the symbol
        sym = request.form.get("symbol")
        if not sym:
            return apology ("Must enter the symbol")

        #Get number of shares and take info about shares user has of that symbol
        sybl = db.execute ("select * from portfolio where id = :ii AND symbol = :sym" , ii = ide,sym = sym)

        #if user has not bought any sahres
        if not sybl:
            return redirect("/") #Go back to index page

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

        #Take all info about user for cash
        row = db.execute ("select * from users where id = :ii" , ii = ide)

        #Lookup and save dict in quoted
        quoted = lookup(sym)

        #If symbol is invalid return apology
        if not quoted:
            return apology ("Invalid stock")

        else:
            #Take price from dict quoted
            qtd = quoted["price"]

            #Multiply current price with number of shares to determine total value of shares sold
            prc = float(qtd)*numb

            #Add current price of the shares to user cash
            db.execute("UPDATE users SET cash = :cash WHERE id = :ide",cash = row[0]["cash"] + prc, ide = ide)

            #Make a negative sale in the portfolio
            db.execute("INSERT INTO portfolio (id, symbol,price,shares,action,dtime) VALUES (:ide, :symbol, :price, :shares,'Sell', DateTime('now'))", ide = ide,symbol = sym, price = prc, shares = -numb)
            return redirect("/")
    else:
        return render_template("sell.html")

    #return apology("TODO")

@app.route("/addcash", methods=["GET", "POST"])
@login_required
def addcash():
    #For personal touch add cash to user
    if request.method == "POST":
        #Take amount to be added
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
            #Take user cash
            row = db.execute ("select cash from users where id = :ii" , ii = session["user_id"])
            #Now add the amount to users data base.
            db.execute("UPDATE users SET cash = :cash WHERE id = :ide",cash = row[0]["cash"] + numb, ide = session["user_id"])
        return redirect("/")

    else:
        #This programe is taking me straight here.
        return render_template("addcash.html")


def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)


# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)