""" Module containing all unit tests for the webserver """

import unittest
import json
from datetime import datetime
from time import sleep
from deepdiff import DeepDiff
import requests

from app.data_ingestor import DataIngestor
from app.task_runner import ThreadPool

def is_server_running():
    """ Function to check if the server is running """
    try:
        requests.get("http://127.0.0.1:5000/api/post_endpoint", timeout=5)
    except requests.exceptions.ConnectionError:
        return False

    return True

class TestWebserver(unittest.TestCase):
    """ Class containing all unit tests for the webserver """
    def setUp(self):
        self.tasks_runner = ThreadPool()
        self.data_ingestor = DataIngestor(
                            "./unittests/in/nutrition_activity_obesity_usa_subset.csv")

    @unittest.skipIf(not is_server_running(), "Server is off")
    def test_get_num_jobs(self):
        """ Test the get_num_jobs endpoint """
        response_data = requests.get("http://127.0.0.1:5000/api/num_jobs", timeout=5)
        self.assertEqual(response_data.status_code, 200)
        with open("unittests/refs/test_get_num_jobs.json", "r", encoding="UTF-8") as fout:
            ref_result = json.load(fout)
            diff = DeepDiff(response_data.json(), ref_result, math_epsilon=0.01)
            self.assertTrue(not diff, str(diff))

    def check_res_timeout(self, res_callable, timeout_sec, poll_interval = 0.2):
        """ Function to wait for the response of a request with a timeout """
        initial_timestamp = datetime.now()
        while True:
            response = res_callable()

            # Asserting that the response status code is 200 (OK)
            self.assertEqual(response.status_code, 200)

            # Asserting the response data
            response_data = response.json()
            # print(f"Response_data\n{response_data}")
            if response_data['status'] == 'done':
                break

            if response_data['status'] == 'error':
                self.fail("Error in response")

            current_timestamp = datetime.now()
            time_delta = current_timestamp - initial_timestamp
            if time_delta.seconds > timeout_sec:
                self.fail("Operation timedout")
            else:
                sleep(poll_interval)

    @unittest.skipIf(not is_server_running(), "Server is off")
    def test_get_jobs(self):
        """ Test the jobs endpoint """
        # make some post requests to create jobs
        test_data = None
        with open("unittests/in/test_get_jobs.json", "r", encoding="UTF-8") as fout:
            test_data = json.load(fout)

        for _ in range(3):
            response_data = requests.post("http://127.0.0.1:5000/api/state_mean",
                                            json=test_data, timeout=5)
            self.assertEqual(response_data.status_code, 200)

            job_id = response_data.json()['job_id']
            url = f"http://127.0.0.1:5000/api/get_results/{job_id}"

            self.check_res_timeout(
                    res_callable = lambda: requests.get(
                            url, timeout=5),
                    timeout_sec = 1)

        ref_result = None
        with open("unittests/refs/test_get_jobs.json", "r", encoding="UTF-8") as fout:
            ref_result = json.load(fout)

        response_data = requests.get("http://127.0.0.1:5000/api/jobs", timeout=5)
        self.assertEqual(response_data.status_code, 200)

        diff = DeepDiff(response_data.json(), ref_result, math_epsilon=0.01)
        self.assertTrue(not diff, str(diff))

    @unittest.skipIf(not is_server_running(), "Server is off")
    def test_graceful_shutdown(self):
        """ Test the graceful shutdown of the server """
        try:
            requests.get("http://127.0.0.1:5000/api/graceful_shutdown", timeout=5)
        except requests.exceptions.ConnectionError:
            pass

        # Wait for the server to shutdown with a timeout
        initial_timestamp = datetime.now()
        while True:
            if not is_server_running():
                break

            current_timestamp = datetime.now()
            time_delta = current_timestamp - initial_timestamp
            if time_delta.seconds > 5:
                self.fail("Server did not shutdown")

    def check_request_validity(self, i, route):
        """ Test the check_request_validity method of the webserver """
        test_data = None
        ref = None

        with open(f"unittests/in/test_check_request_validity{i}.json",
                  "r", encoding="UTF-8") as fout:
            test_data = json.load(fout)

        with open(f"unittests/refs/test_check_request_validity{i}.json",
                    "r", encoding="UTF-8") as fout:
            ref = json.load(fout)

        response = requests.post(f"http://127.0.0.1:5000{route}",
                                            json=test_data, timeout=5)
        response_data = response.json()

        ref_status_code = ref["status_code"]
        ref_data = ref["data"]

        self.assertEqual(response.status_code, ref_status_code)
        self.compare_json(response_data, ref_data)

    @unittest.skipIf(not is_server_running(), "Server is off")
    def test_check_request_validity1(self):
        """ Test if the server accepts valid requests """
        self.check_request_validity(1, "/api/states_mean")

    @unittest.skipIf(not is_server_running(), "Server is off")
    def test_check_request_validity2(self):
        """ Test if the server catches requests with no questions """
        self.check_request_validity(2, "/api/states_mean")

    @unittest.skipIf(not is_server_running(), "Server is off")
    def test_check_request_validity3(self):
        """ Test if the server catches requests with invalid questions """
        self.check_request_validity(3, "/api/states_mean")

    @unittest.skipIf(not is_server_running(), "Server is off")
    def test_check_request_validity4(self):
        """ Test if the server catches requests with no json data """
        response = requests.post("http://127.0.0.1:5000/api/states_mean", timeout=5)

        self.assertEqual(response.status_code, 400)
        self.compare_ref_output(response.json(), "unittests/refs/test_check_request_validity4.json")

    @unittest.skipIf(not is_server_running(), "Server is off")
    def test_check_request_validity_with_state_name(self):
        """ Test if the server catches requests with no state name """
        self.check_request_validity(5, "/api/state_mean")

    @unittest.skipIf(not is_server_running(), "Server is off")
    def test_check_invalid_job_id(self):
        """ Test if the server catches invalid job ids """
        response = requests.get("http://127.0.0.1:5000/api/get_results/0", timeout=5)

        self.assertEqual(response.status_code, 400)
        self.compare_ref_output(response.json(), "unittests/refs/test_check_invalid_job_id.json")

        response = requests.get("http://127.0.0.1:5000/api/get_results/1923", timeout=5)

        self.assertEqual(response.status_code, 400)
        self.compare_ref_output(response.json(), "unittests/refs/test_check_invalid_job_id.json")

    # Test the task runner
    def test_get_last_job_id(self):
        """ Test the get_last_job_id method of the task runner """
        self.tasks_runner.get_job_id()
        self.tasks_runner.get_job_id()
        self.tasks_runner.get_job_id()
        output = self.tasks_runner.get_last_job_id()
        self.assertEqual(output, 3)

    def test_get_job_id(self):
        """ Test the get_job_id method of the task runner """
        output = self.tasks_runner.get_job_id()
        self.assertEqual(output, 1)

        output = self.tasks_runner.get_job_id()
        self.assertEqual(output, 2)

        output = self.tasks_runner.get_job_id()
        output = self.tasks_runner.get_job_id()
        output = self.tasks_runner.get_job_id()

        self.assertEqual(output, 5)

    def test_get_last_finished_job_id(self):
        """ Test the get_last_finished_job_id method of the task runner """
        self.assertEqual(self.tasks_runner.get_last_finished_job_id(), 0)

        self.tasks_runner.update_last_finished_job_id()
        self.tasks_runner.update_last_finished_job_id()
        output = self.tasks_runner.get_last_finished_job_id()
        self.assertEqual(output, 2)

    def test_get_remaining_job_count(self):
        """ Test the get_remaining_job_count method of the task runner """
        self.tasks_runner.get_job_id()
        self.tasks_runner.get_job_id()
        self.tasks_runner.update_last_finished_job_id()
        output = self.tasks_runner.get_remaining_job_count()
        self.assertEqual(output, 1)

    # Test the data ingestor
    def test_get_questions(self):
        """ Test the get_questions method of the data ingestor """
        output = self.data_ingestor.get_questions()

        with open("unittests/refs/test_get_questions.txt", "r", encoding="UTF-8") as fout:
            # get lines
            ref = fout.readlines()
            ref = [line.strip() for line in ref]

            self.assertEqual(len(output), len(ref))

            for line in ref:
                self.assertTrue(line in output)

    def compare_json(self, output, ref):
        """ Function to compare two json objects"""
        diff = DeepDiff(output, ref, math_epsilon=0.01)
        self.assertTrue(not diff, str(diff))

    def compare_ref_output(self, output, ref_file):
        """ Function to compare the output of a method with a reference file """
        with open(ref_file, "r", encoding="UTF-8") as fout:
            ref_result = json.load(fout)
            self.compare_json(output, ref_result)

    def get_input_question(self, file_name):
        """ Function to get the input question from a file """
        with open(file_name, "r", encoding="UTF-8") as fout:
            return json.load(fout)["question"]

    def get_input_question_and_state(self, file_name):
        """ Function to get the input question and state from a file """
        with open(file_name, "r", encoding="UTF-8") as fout:
            json_data = json.load(fout)
            state = self.data_ingestor.states[json_data["state"]]
            return json_data["question"], state

    def get_ref_output(self, file_name):
        """ Function to get the reference output from a file """
        result = []
        with open(file_name, "r", encoding="UTF-8") as fout:
            ref = json.load(fout)

            array = ref["data"]

            for i in array:
                for key, value in i.items():
                    result.append((key, value))

        return result

    def float_equals(self, a, b, epsilon=0.01):
        """ Function to compare two floats """
        return abs(a - b) < epsilon

    def test_mean_states(self):
        """ Test the mean_states method of the data ingestor """
        question = self.get_input_question("unittests/in/test_mean_states.json")
        output_ref = self.get_ref_output("unittests/refs/test_mean_states.json")

        output = self.data_ingestor.mean_states(question)

        self.assertTrue(output == sorted(output, key=lambda x: x[1]))
        self.assertTrue(output == output_ref)

    def test_mean_state(self):
        """ Test the mean_state method of the data ingestor """
        question, state = self.get_input_question_and_state("unittests/in/test_mean_state.json")

        output = self.data_ingestor.mean_state(state, question)
        self.assertTrue(self.float_equals(output, 31.3))

    def test_get_best5(self):
        """ Test the get_best5_states method of the data ingestor """
        question = self.get_input_question("unittests/in/test_get_best5.json")

        output = self.data_ingestor.best5(question)
        output = json.loads(output)

        self.compare_ref_output(output, "unittests/refs/test_get_best5.json")

    def test_get_worst5(self):
        """ Test the get_worst5_states method of the data ingestor """
        question = self.get_input_question("unittests/in/test_get_worst5.json")

        output = self.data_ingestor.worst5(question)
        output = json.loads(output)

        self.compare_ref_output(output, "unittests/refs/test_get_worst5.json")

    def test_global_mean(self):
        """ Test the global_mean method of the data ingestor """
        question = self.get_input_question("unittests/in/test_global_mean.json")

        output = self.data_ingestor.global_mean(question)

        self.assertTrue(self.float_equals(output, 32.0625))

    def test_diff_from_mean(self):
        """ Test the diff_from_mean method of the data ingestor """
        question = self.get_input_question("unittests/in/test_diff_from_mean.json")

        output = self.data_ingestor.diff_from_mean(question)

        self.compare_ref_output(output, "unittests/refs/test_diff_from_mean.json")

    def test_state_diff_from_mean(self):
        """ Test the state_diff_from_mean method of the data ingestor """
        question, state = self.get_input_question_and_state(
                                "unittests/in/test_state_diff_from_mean.json")

        output = self.data_ingestor.state_diff_from_mean(state, question)

        self.assertTrue(self.float_equals(output, -4.983333333333334))

    def test_mean_by_category(self):
        """ Test the mean_by_category method of the data ingestor """
        question = self.get_input_question("unittests/in/test_mean_by_category.json")

        output = self.data_ingestor.mean_by_category_wrapper(question)
        output = json.loads(output)

        self.compare_ref_output(output, "unittests/refs/test_mean_by_category.json")

    def test_state_mean_by_category(self):
        """ Test the state_mean_by_category method of the data ingestor """
        question, state = self.get_input_question_and_state(
                                "unittests/in/test_state_mean_by_category.json")

        output = self.data_ingestor.state_mean_by_category_wrapper(state.name, question)
        output = json.loads(output)

        self.compare_ref_output(output, "unittests/refs/test_state_mean_by_category.json")

if __name__ == "__main__":
    unittest.main()
