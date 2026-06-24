from flask import Flask, render_template
import serial
import threading

app = Flask(__name__)

latest_distance = "-"

def read_serial():
    global latest_distance
    ser = serial.Serial('COM3', 9600, timeout=1)
    while True:
        line = ser.readline().decode().strip()
        if line:
            latest_distance = line

# 백그라운드에서 시리얼 계속 읽기
t = threading.Thread(target=read_serial, daemon=True)
t.start()

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/distance')
def get_distance():
    return latest_distance

if __name__ == '__main__':
    app.run(debug=False)