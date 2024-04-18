from flask_login import UserMixin
from flask_wtf import FlaskForm
from wtforms import StringField, PasswordField, SubmitField
from wtforms.validators import InputRequired, Length, ValidationError
from db import User

class RegisterForm(FlaskForm):
    username = StringField(validators=[
        InputRequired(), Length(min=4, max=250)
        ], 
        render_kw={"placeholder": "Username"})
    password = PasswordField(validators=[
        InputRequired(), Length(min=4, max=250)
        ], 
        render_kw={"placeholder": "Password"})
    submit = SubmitField("Register")

    def validate_username(self, username):
        existing_user_username = User.query.filter_by(
            username=username.data).first()
        
        if existing_user_username:
            raise ValidationError(
                "That username already exists. Please choose a different one."
            )

class LoginForm(FlaskForm):
    username = StringField(validators=[
        InputRequired(), Length(min=4, max=250)
        ], 
        render_kw={"placeholder": "Username"})
    password = PasswordField(validators=[
        InputRequired(), Length(min=4, max=250)
        ], 
        render_kw={"placeholder": "Password"})
    submit = SubmitField("Login")
