""" Module for testing the pixegami.io API """
import unittest
import uuid
import requests

class TestAPI(unittest.TestCase):
    """ Test the pixegami.io API """
    def test_create_task(self):
        """ Test the /create-task endpoint and /get-task/{task-id} endpoint """
        content = "Write tests for pixegami.io API"
        user_id = uuid.uuid1().hex
        is_done = False
        json_data = {
            "content": content,
            "user_id": user_id,
            "task_id": "not_relevant",
            "is_done": is_done
        }
        response = requests.put('https://todo.pixegami.io/create-task',
                                 json=json_data,
                                timeout=5)
        self.assertEqual(response.status_code, 200)

        task_id = response.json()['task']['task_id']

        response = requests.get(f'https://todo.pixegami.io/get-task/{task_id}',
                                timeout=5)
        self.assertEqual(response.status_code, 200)
        self.assertEqual(response.json()['content'], content)
        self.assertEqual(response.json()['user_id'], user_id)
        self.assertEqual(response.json()['is_done'], is_done)
        self.assertEqual(response.json()['task_id'], task_id)

    def test_update_task(self):
        """ Test the /update-task endpoint (and its interaction with the /create-task and
            /get-task/{task-id} endpoints) """
        content = "Meet the penguins"
        user_id = uuid.uuid1().hex
        is_done = False
        json_data = {
            "content": content,
            "user_id": user_id,
            "task_id": "not_relevant",
            "is_done": is_done
        }

        response = requests.put('https://todo.pixegami.io/create-task',
                                json=json_data,
                                timeout=5)
        self.assertEqual(response.status_code, 200)

        task_id = response.json()['task']['task_id']

        content = "Meet the elephants"
        is_done = True
        json_data = {
            "content": content,
            "user_id": user_id,
            "task_id": task_id,
            "is_done": is_done
        }

        response = requests.put('https://todo.pixegami.io/update-task',
                                json=json_data,
                                timeout=5)
        self.assertEqual(response.status_code, 200)

        response = requests.get(f'https://todo.pixegami.io/get-task/{task_id}',
                                timeout=5)

        self.assertEqual(response.status_code, 200)
        self.assertEqual(response.json()['content'], content)
        self.assertEqual(response.json()['user_id'], user_id)
        self.assertEqual(response.json()['is_done'], is_done)
        self.assertEqual(response.json()['task_id'], task_id)

    def test_list_tasks(self):
        """ Test the /list-tasks endpoint """
        content = "bamboleo"
        user_id = uuid.uuid1().hex
        is_done = False
        json_data = {
            "content": content,
            "user_id": user_id,
            "task_id": "not_relevant",
            "is_done": is_done
        }
        response = requests.put('https://todo.pixegami.io/create-task',
                    json=json_data,
                    timeout=5)
        self.assertEqual(response.status_code, 200)

        content = "bambolea"
        json_data = {
            "content": content,
            "user_id": user_id,
            "task_id": "not_relevant",
            "is_done": is_done
        }

        response = requests.put('https://todo.pixegami.io/create-task',
                    json=json_data,
                    timeout=5)
        self.assertEqual(response.status_code, 200)

        content = "bembele"
        json_data = {
            "content": content,
            "user_id": user_id,
            "task_id": "not_relevant",
            "is_done": is_done
        }

        response = requests.put('https://todo.pixegami.io/create-task',
                                json=json_data,
                                timeout=5)
        self.assertEqual(response.status_code, 200)

        response = requests.get(f'https://todo.pixegami.io/list-tasks/{user_id}',
                                timeout=5)
        self.assertEqual(response.status_code, 200)
        self.assertEqual(len(response.json()['tasks']), 3)

    def test_delete_task(self):
        """ Test the /delete-task endpoint """
        content = "fetti on fetti on fetti"
        user_id = uuid.uuid1().hex
        is_done = False
        json_data = {
            "content": content,
            "user_id": user_id,
            "task_id": "not_relevant",
            "is_done": is_done
        }

        response = requests.put('https://todo.pixegami.io/create-task',
                                json=json_data,
                                timeout=5)
        self.assertEqual(response.status_code, 200)

        task_id = response.json()['task']['task_id']

        response = requests.delete(f'https://todo.pixegami.io/delete-task/{task_id}',
                                   timeout=5)
        self.assertEqual(response.status_code, 200)

        response = requests.get(f'https://todo.pixegami.io/get-task/{task_id}',
                                timeout=5)
        self.assertEqual(response.status_code, 404)
