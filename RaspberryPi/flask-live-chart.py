import json
from time import time
from random import randrange
from flask import Flask, render_template, make_response
#import operate as op

app = Flask(__name__)


@app.route('/')
def hello_world():
    return render_template('index.html', data='test')

@app.route('/live-data')
def live_data():
    # Create a PHP array and echo it as JSON
    data = [time() * 1000, op.routine(b'2'), op.routine(b'1'), op.routine(b'0')]
    response = make_response(json.dumps(data))
    response.content_type = 'application/json'
    return response

if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0', port=5000)
