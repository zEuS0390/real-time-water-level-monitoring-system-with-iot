from app import create_app, socketio
from flask_login import current_user
from flask_socketio import disconnect
from views_bp import views_bp
from app import mqtt

app = create_app()

@socketio.on('connect')
def connect_handler():
    if current_user.is_authenticated:
        print(current_user.username)
        mqtt.subscribe("group11/rain") # subscribe topic
        mqtt.subscribe("group11/water") # subscribe topic
        mqtt.subscribe("group11/distance") # subscribe topic
    else:
        disconnect()
        return False  # not allowed here
    
@mqtt.on_connect()
def handle_connect(client, userdata, flags, rc):
   if rc == 0:
        print('Connected successfully')
   else:
       print('Bad connection. Code:', rc)
    
@mqtt.on_message()
def handle_mqtt_message(client, userdata, message):
    topic = message.topic
    payload = message.payload.decode()
    print(f"Received message on topic: {topic}, payload: {payload}")
    if topic == "group11/rain":
        socketio.emit(topic, payload)
        print(topic)
    elif topic == "group11/water":
        socketio.emit(topic, payload)
        print(topic)
    elif topic == "group11/distance":
        socketio.emit(topic, payload)
        print(topic)

app.register_blueprint(views_bp)

if __name__=="__main__":
  socketio.run(app, debug=True, host='0.0.0.0')
