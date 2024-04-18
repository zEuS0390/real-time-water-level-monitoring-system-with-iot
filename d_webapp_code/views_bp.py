from flask import Blueprint, render_template, redirect, url_for
from db import db
from app import bcrypt
from forms import *

from flask_login import login_user, logout_user, current_user

views_bp = Blueprint("views_bp", __name__)

@views_bp.route("/")
def home():
  if not current_user.is_authenticated:
    return render_template("home.html")
  return redirect(url_for("views_bp.dashboard"))

@views_bp.route("/login", methods=["GET", "POST"])
def login():
  if not current_user.is_authenticated:
    form = LoginForm()
    if form.validate_on_submit():
      user = User.query.filter_by(username=form.username.data).first()
      if user:
        if bcrypt.check_password_hash(user.password, form.password.data):
          login_user(user)
          return redirect(url_for("views_bp.dashboard"))
    return render_template("login.html", form=form)
  return redirect(url_for("views_bp.dashboard"))

@views_bp.route("/logout")
def logout():
  logout_user()
  return redirect(url_for("views_bp.login"))

@views_bp.route("/register", methods=["GET", "POST"])
def register():
  if not current_user.is_authenticated:
    form = RegisterForm()
    if form.validate_on_submit():
      hashed_password = bcrypt.generate_password_hash(form.password.data)
      new_user = User(username=form.username.data, password=hashed_password)
      db.session.add(new_user)
      db.session.commit()
      return redirect(url_for('views_bp.login'))
    return render_template("register.html", form=form)
  return redirect(url_for("views_bp.dashboard"))

@views_bp.route("/dashboard", methods=["GET", "POST"])
def dashboard():
  if current_user.is_authenticated:
    return render_template("dashboard.html")
  return redirect(url_for("views_bp.login"))