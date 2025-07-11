""" Module containing all webserver API endpoints """
import os
import json
import logging
from flask import request, jsonify
from app import webserver

@webserver.route('/api/post_endpoint', methods=['POST'])
def post_endpoint():
    """ Example of a POST endpoint """
    if request.method == 'POST':
        # Assuming the request contains JSON data
        data = request.json
        print(f"got data in post {data}")

        # Process the received data
        # For demonstration purposes, just echoing back the received data
        response = {"message": "Received data successfully", "data": data}

        # Sending back a JSON response
        return jsonify(response)

    # Method Not Allowed
    return jsonify({"error": "Method not allowed"}), 405

@webserver.route('/api/get_results/<job_id>', methods=['GET'])
def get_response(job_id):
    """ Returns the status of a job and its result if it's done """
    # Check if the job_id is valid
    if int(job_id) > webserver.tasks_runner.get_last_job_id() or int(job_id) < 1:
        logging.error('Received request for result of invalid job_id: %s', job_id)
        return jsonify({'status': 'error',
                        'reason': 'Invalid job_id',}), 400

    path_to_result = f"results/{job_id}"

    if os.path.exists(path_to_result):
        with open(path_to_result, "r", encoding="UTF-8") as file:
            res = json.load(file)
            logging.info('Received request for result of job_id: %s. Status: done', job_id)
            return jsonify({
                'status': 'done',
                'data': res
            })

    # If not, return running status
    logging.info('Received request for result of job_id: %s. Status: pending', job_id)
    return jsonify({'status': 'running',})

def check_request_validity(incoming_request):
    """ Check if the question is valid, return a boolean and
        an error message and code in case the request is invalid """
    if webserver.tasks_runner.graceful_shutdown_event.is_set():
        logging.error('Received request at %s while shutting down', incoming_request.path)
        return False, {"job_id": -1, "reason": "shutting down" }, 503

    if not incoming_request.is_json:
        logging.error('Request at %s does not contain a JSON object', incoming_request.path)
        return False, {"error": "Request must be a JSON object"}, 400

    if 'question' not in incoming_request.json:
        logging.error('Request at %s does not contain a "question" field', incoming_request.path)
        return False, {"error":
                        f"Request at {incoming_request.path} must contain a 'question' field"}, 400

    if incoming_request.json['question'] not in webserver.data_ingestor.get_questions():
        logging.error('Request at %s contains an invalid question', incoming_request.path)
        return False, {"error": f"Invalid question: {incoming_request.json['question']}"}, 400

    return True, None, None

def check_request_validity_with_state_name(incoming_request):
    """ Check if the question is valid with the added condition of the state name being set,
        return a boolean and an error message in case the request is invalid """
    valid, message, code = check_request_validity(incoming_request)

    if not valid:
        return valid, message, code

    if 'state' not in incoming_request.json:
        logging.error('Request at %s does not contain a "state" field', incoming_request.path)
        return False, {"error":
                         f"Request at {incoming_request.path} must contain a 'state' field"}, 400

    return True, None, None

@webserver.route('/api/states_mean', methods=['POST'])
def states_mean_request():
    """ Endpoint to calculate the mean of all states """
    valid, message, code = check_request_validity(request)

    if not valid:
        return jsonify(message), code

    # Get request data
    data = request.json

    # Register job. Don't wait for task to finish
    # Increment job_id counter
    job_id = webserver.tasks_runner.get_job_id()
    question = data['question']
    def states_mean_closure():
        """ Closure to calculate the mean of a given state, returns the job id and the result """
        return job_id, webserver.data_ingestor.mean_states_wrapper(question)

    webserver.tasks_runner.add_task(states_mean_closure)

    logging.info('Job %d created: calculate the mean of all states for question "%s"',
                  job_id, data['question'])

    # Return associated job_id
    return jsonify({"job_id": job_id})

@webserver.route('/api/state_mean', methods=['POST'])
def state_mean_request():
    """ Endpoint to calculate the mean of a specific state """
    valid, message, code = check_request_validity_with_state_name(request)

    if not valid:
        return jsonify(message), code

    # Get request data
    data = request.json

    # Register job. Don't wait for task to finish
    # Increment job_id counter
    job_id = webserver.tasks_runner.get_job_id()
    state_name = data['state']
    question = data['question']

    def state_mean_closure():
        """ Closure to calculate the mean of a given state, returns the job id and the result """
        return job_id, webserver.data_ingestor.mean_state_wrapper(state_name, question)

    webserver.tasks_runner.add_task(state_mean_closure)

    logging.info('Job %d created: calculate the mean of state "%s" for question "%s"',
                    job_id, state_name, question)

    # Return associated job_id
    return jsonify({"job_id": job_id})


@webserver.route('/api/best5', methods=['POST'])
def best5_request():
    """ Endpoint to calculate the top 5 states with the best values for a given question
        The best values can be either the minimum or maximum value, depending on the question """
    valid, message, code = check_request_validity(request)

    if not valid:
        return jsonify(message), code

    # Get request data
    data = request.json
    # Register job. Don't wait for task to finish
    # Increment job_id counter
    job_id = webserver.tasks_runner.get_job_id()
    question = data['question']

    def best5_closure():
        return job_id, webserver.data_ingestor.best5(question)

    webserver.tasks_runner.add_task(best5_closure)

    logging.info('Job %d created: calculate the best 5 states for question "%s"',
                    job_id, question)

    # Return associated job_id
    return jsonify({"job_id": job_id})

@webserver.route('/api/worst5', methods=['POST'])
def worst5_request():
    """ Endpoint to calculate the bottom 5 states with the worst values for a given question
        The worst values can be either the minimum or maximum value, depending on the question """
    valid, message, code = check_request_validity(request)

    if not valid:
        return jsonify(message), code

    # Get request data
    data = request.json
    # Register job. Don't wait for task to finish
    # Increment job_id counter
    job_id = webserver.tasks_runner.get_job_id()
    question = data['question']

    def worst5_closure():
        return job_id, webserver.data_ingestor.worst5(question)

    webserver.tasks_runner.add_task(worst5_closure)

    logging.info('Job %d created: calculate the worst 5 states for question "%s"',
                    job_id, question)

    # Return associated job_id
    return jsonify({"job_id": job_id})

@webserver.route('/api/global_mean', methods=['POST'])
def global_mean_request():
    """ Endpoint to calculate the global mean of a given question """
    valid, message, code = check_request_validity(request)

    if not valid:
        return jsonify(message), code

    # Get request data
    data = request.json
    # Register job. Don't wait for task to finish
    # Increment job_id counter
    job_id = webserver.tasks_runner.get_job_id()
    question = data['question']

    def global_mean_closure():
        return job_id, webserver.data_ingestor.global_mean_wrapper(question)

    webserver.tasks_runner.add_task(global_mean_closure)

    logging.info('Job %d created: calculate the global mean for question "%s"',
                    job_id, question)

    # Return associated job_id
    return jsonify({"job_id": job_id})

@webserver.route('/api/diff_from_mean', methods=['POST'])
def diff_from_mean_request():
    """ Computes all the differences between the global mean and the state mean
        for a given question """
    valid, message, code = check_request_validity(request)

    if not valid:
        return jsonify(message), code

    # Get request data
    data = request.json
    # Register job. Don't wait for task to finish
    # Increment job_id counter
    job_id = webserver.tasks_runner.get_job_id()
    question = data['question']

    def diff_from_mean_closure():
        return job_id, webserver.data_ingestor.diff_from_mean_wrapper(question)

    webserver.tasks_runner.add_task(diff_from_mean_closure)

    logging.info('Job %d created: calculate the difference from the global mean for question "%s"',
                    job_id, question)

    # Return associated job_id
    return jsonify({"job_id": job_id})

@webserver.route('/api/state_diff_from_mean', methods=['POST'])
def state_diff_from_mean_request():
    """ Endpoint to compute the difference between a state's value and
        the global mean given a question """
    valid, message, code = check_request_validity_with_state_name(request)

    if not valid:
        return jsonify(message), code

    # Get request data
    data = request.json
    state_name = data['state']
    # Register job. Don't wait for task to finish
    # Increment job_id counter
    job_id = webserver.tasks_runner.get_job_id()
    question = data['question']

    def state_diff_from_mean_closure():
        return job_id, webserver.data_ingestor.state_diff_from_mean_wrapper(state_name, question)

    webserver.tasks_runner.add_task(state_diff_from_mean_closure)

    logging.info(
        'Job %d created: calculate the diff from the global mean for state "%s" and question "%s"',
        job_id, state_name, question)

    # Return associated job_id
    return jsonify({"job_id": job_id})

@webserver.route('/api/mean_by_category', methods=['POST'])
def mean_by_category_request():
    """ Endpoint to calculate the mean of all states according to a question and
        for all stratification categories """
    valid, message, code = check_request_validity(request)

    if not valid:
        return jsonify(message), code

    # Get request data
    data = request.json
    # Register job. Don't wait for task to finish
    # Increment job_id counter
    job_id = webserver.tasks_runner.get_job_id()
    question = data['question']

    def mean_by_category_closure():
        return job_id, webserver.data_ingestor.mean_by_category_wrapper(question)

    webserver.tasks_runner.add_task(mean_by_category_closure)

    logging.info('Job %d created: calculate the mean by category for question "%s"',
                    job_id, question)

    # Return associated job_id
    return jsonify({"job_id": job_id})

@webserver.route('/api/state_mean_by_category', methods=['POST'])
def state_mean_by_category_request():
    """ Endpoint to calculate the mean of a specific state according to a question and
        for all stratification categories """
    valid, message, code = check_request_validity_with_state_name(request)

    if not valid:
        return jsonify(message), code

    # Get request data
    data = request.json
    # Register job. Don't wait for task to finish
    # Increment job_id counter
    job_id = webserver.tasks_runner.get_job_id()
    question = data['question']
    state_name = data['state']

    def state_mean_by_category_closure():
        return job_id, webserver.data_ingestor.state_mean_by_category_wrapper(state_name, question)

    webserver.tasks_runner.add_task(state_mean_by_category_closure)

    logging.info('Job %d created: calculate the mean by category for state "%s" and question "%s"',
                    job_id, state_name, question)

    # Return associated job_id
    return jsonify({"job_id": job_id})


@webserver.route('/api/graceful_shutdown', methods=['GET'])
def graceful_shutdown():
    """ Gracefully shutdown the webserver """
    # Stop the webserver
    logging.info("Received request to stop the webserver")
    webserver.tasks_runner.graceful_shutdown()

    webserver.job_counter = 0

    return jsonify({"message": "Webserver has been stopped"})

@webserver.route('/api/jobs', methods=['GET'])
def get_jobs():
    """ Return all jobs and their status """
    logging.info("Received request for list of jobs")
    result = {"status": "done", "data": []}
    last_finished_job_id = webserver.tasks_runner.get_last_finished_job_id()

    for job_id in range(1, last_finished_job_id + 1):
        result['data'].append({f"job_id_{job_id}": "done"})

    for job_id in range(last_finished_job_id + 1, webserver.tasks_runner.get_last_job_id() + 1):
        result['data'].append({f"job_id_{job_id}": "running"})

    return jsonify(result)

@webserver.route('/api/num_jobs', methods=['GET'])
def get_num_jobs():
    """ Get the number of jobs that are being processed """
    logging.info("Received request for the number of jobs being processed")
    return jsonify({"num_jobs": webserver.tasks_runner.get_remaining_job_count()})

# You can check localhost in your browser to see what this displays
@webserver.route('/')
@webserver.route('/index')
def index():
    """ Displays the available routes """
    routes = get_defined_routes()
    msg = "Hello, World!\n Interact with the webserver using one of the defined routes:\n"

    # Display each route as a separate HTML <p> tag
    paragraphs = ""
    for route in routes:
        paragraphs += f"<p>{route}</p>"

    msg += paragraphs
    return msg

def get_defined_routes():
    """ Returns a list of all defined routes in the webserver """
    routes = []
    for rule in webserver.url_map.iter_rules():
        methods = ', '.join(rule.methods)
        routes.append(f"Endpoint: \"{rule}\" Methods: \"{methods}\"")
    return routes
