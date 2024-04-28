from app import create_app, socketio
from flask_login import current_user
from flask_socketio import disconnect
from views_bp import views_bp

app = create_app()

@socketio.on('connect')
def connect_handler():
    try:
        if current_user.is_authenticated:
            print(f"{current_user.username} IS AUTHENTICATED?: {current_user.is_authenticated}")
        else:
            disconnect()
            return False  # not allowed here
    except:
        disconnect()
        return False

app.register_blueprint(views_bp)

if __name__=="__main__":
    socketio.run(app, debug=True, host='0.0.0.0', use_reloader=False)
