from flask import Flask
from flask_bcrypt import Bcrypt
from flask_login import LoginManager
import paho.mqtt.client as Mqtt
from flask_socketio import SocketIO
from db import db, User
import uuid

bcrypt = Bcrypt()
login_manager = LoginManager()
mqtt = Mqtt.Client(Mqtt.CallbackAPIVersion.VERSION2, f"MQTT-SOCKETIO-BRIDGE-{uuid.uuid4()}", clean_session=True)
socketio = SocketIO()

MQTT_BROKER_URL = 'mosquitto'
MQTT_BROKER_PORT = 1883         # default port for non-tls connection
MQTT_USERNAME = 'user'          # set the username here if you need authentication for the broker
MQTT_PASSWORD = 'pass123'       # set the password here if the broker demands authentication

def handle_mqtt_connect(client, userdata, flags, reasonCode, properties):
    if reasonCode == 0: 
        print('Connected successfully')
        mqtt.subscribe("group11")
    else: print('Bad connection. Code:', reasonCode)
    
def handle_mqtt_message(client, userdata, message):
    topic = message.topic
    payload = message.payload.decode()
    socketio.emit(topic, payload)

def create_app():
  app = Flask(__name__)

  app.config["SQLALCHEMY_DATABASE_URI"] = "sqlite:///database.db"
  app.config["SECRET_KEY"] = "my-secret"

  db.init_app(app)
  bcrypt.init_app(app)
  login_manager.init_app(app)
  socketio.init_app(app, async_mode="eventlet", cors_allowed_origins="*")

  with app.app_context():
    db.create_all()

  mqtt.on_connect = handle_mqtt_connect
  mqtt.on_message = handle_mqtt_message
  mqtt.username_pw_set(MQTT_USERNAME, MQTT_PASSWORD)
  mqtt.connect(MQTT_BROKER_URL, MQTT_BROKER_PORT)
  mqtt.loop_start()

  return app

@login_manager.user_loader
def load_user(user_id):
    return User.query.get(int(user_id))
