from app import create_app, socketio
from views_bp import views_bp

app = create_app()

app.register_blueprint(views_bp)

if __name__=="__main__":
    socketio.run(app, debug=True, host='0.0.0.0', use_reloader=False)
