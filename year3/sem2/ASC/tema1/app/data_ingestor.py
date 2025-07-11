""" Module for parsing and storage of the obesity data"""
import json
import csv
import math

class State:
    """ State class to store information about a certain state"""
    def __init__(self, name, rows):
        self.name = name
        self.rows = rows
        self.question_to_rows = {}
        self.question_to_stratification_to_rows = {}

        for row in rows:
            # Group rows by question
            question = row['Question']
            if question not in self.question_to_rows:
                self.question_to_rows[question] = [row]
            else:
                self.question_to_rows[question].append(row)

            # Group rows by question/stratification
            stratification = (row['StratificationCategory1'], row['Stratification1'])

            if stratification[0] == "" or stratification[1] == "":
                continue

            if question not in self.question_to_stratification_to_rows:
                self.question_to_stratification_to_rows[question] = {stratification: [row]}
            else:
                if stratification not in self.question_to_stratification_to_rows[question]:
                    self.question_to_stratification_to_rows[question][stratification] = [row]
                else:
                    self.question_to_stratification_to_rows[question][stratification].append(row)

    def get_rows_by_question(self, question):
        """ Get the row by question """
        return self.question_to_rows[question]

    def get_rows_by_stratification(self, question, stratification):
        """ Get the row by stratification """
        return self.question_to_stratification_to_rows[question][stratification]

class DataIngestor:
    """ Class that parses a csv file and stores it in a structured way """
    def __init__(self, csv_path: str):
        with open(csv_path, 'r', encoding='utf-8') as csv_file:
            csv_dict = csv.DictReader(csv_file)

            # Group rows by state
            self.state_info = {}

            for row in csv_dict:
                if row["LocationDesc"] not in self.state_info:
                    self.state_info[row['LocationDesc']] = [row]
                else:
                    self.state_info[row['LocationDesc']].append(row)

            self.states = {}

            for state_name, rows in self.state_info.items():
                self.states[state_name] = State(state_name, rows)

        self.questions_best_is_min = [
            'Percent of adults aged 18 years and older who have an overweight classification',
            'Percent of adults aged 18 years and older who have obesity',
            'Percent of adults who engage in no leisure-time physical activity',
            'Percent of adults who report consuming fruit less than one time daily',
            'Percent of adults who report consuming vegetables less than one time daily'
        ]

        self.questions_best_is_max = [
            'Percent of adults who achieve at least 150 minutes a week of moderate-intensity aerobic physical activity or 75 minutes a week of vigorous-intensity aerobic activity (or an equivalent combination)',
            'Percent of adults who achieve at least 150 minutes a week of moderate-intensity aerobic physical activity or 75 minutes a week of vigorous-intensity aerobic physical activity and engage in muscle-strengthening activities on 2 or more days a week',
            'Percent of adults who achieve at least 300 minutes a week of moderate-intensity aerobic physical activity or 150 minutes a week of vigorous-intensity aerobic activity (or an equivalent combination)',
            'Percent of adults who engage in muscle-strengthening activities on 2 or more days a week',
        ]

        self.all_questions = set()
        self.all_questions.update(self.questions_best_is_min)
        self.all_questions.update(self.questions_best_is_max)

    def get_questions(self):
        """ Get all the questions in the data """
        return self.all_questions

    def mean_state(self, state: State, question: str):
        """ Calculate the mean of a question for a state """
        if question not in state.question_to_rows:
            return float('nan')

        rows = state.get_rows_by_question(question)

        mean = 0.0
        length = 0.0

        for row in rows:
            value = row['Data_Value']
            try:
                value = float(value)
            except ValueError:
                continue

            mean += value
            length += 1.0

        try:
            return mean / length
        except ZeroDivisionError:
            return float('nan')

    def mean_state_wrapper(self, state_name: str, question: str):
        """ Wraps the mean_state function to return a json string """
        dict_result = {state_name: self.mean_state(self.states[state_name], question)}
        return json.dumps(dict_result)


    def mean_states(self, question: str):
        """ Calculate the mean of a question for all states and
            returns a sorted list of all answers """
        states = self.states.values()
        means = {}
        for state in states:
            if question not in state.question_to_rows:
                continue

            means[state.name] = self.mean_state(state, question)

        state_mean_pairs = list(means.items())

        return sorted(state_mean_pairs, key=lambda x: x[1])

    def mean_states_wrapper(self, question: str):
        """ Wraps the mean_states function to return a json string """
        json_result = {}

        for state, mean in self.mean_states(question):
            json_result[state] = mean

        return json.dumps(json_result)

    def get_first5_as_json(self, state_means):
        """ Return the first 5 elements of a list as a JSON string """
        json_result = {}

        first5 = state_means[:5]

        for state, mean in first5:
            json_result[state] = mean

        return json.dumps(json_result)

    def get_last5_as_json(self, state_means):
        """ Return the last 5 elements of a list as a JSON string """
        json_result = {}
        last5 = state_means[-5:]
        last5 = last5[::-1]

        for state, mean in last5:
            json_result[state] = mean

        return json.dumps(json_result)

    def best5(self, question: str):
        """ Calculate the best 5 states for a given question """
        # Filter out NaN values
        sorted_states_by_mean = list(filter(lambda mean_state: not math.isnan(mean_state[1]),
                                            self.mean_states(question)))

        # Determine which states are the best and return them as a JSON string
        if question in self.questions_best_is_min:
            return self.get_first5_as_json(sorted_states_by_mean)

        if question in self.questions_best_is_max:
            return self.get_last5_as_json(sorted_states_by_mean)

        return []

    def worst5(self, question: str):
        """ Calculate the worst 5 states for a given question """
        sorted_states_by_mean = self.mean_states(question)

        if question in self.questions_best_is_min:
            return self.get_last5_as_json(sorted_states_by_mean)

        if question in self.questions_best_is_max:
            return self.get_first5_as_json(sorted_states_by_mean)

        return []

    def global_mean(self, question: str):
        """ Calculate the global mean for a given question """
        total_mean = 0.0
        total_length = 0.0

        for state in self.states.values():
            if question not in state.question_to_rows:
                continue

            rows = state.get_rows_by_question(question)

            for row in rows:
                value = row['Data_Value']
                try:
                    value = float(value)
                except ValueError:
                    continue

                total_mean += value
                total_length += 1.0

        try:
            return total_mean / total_length
        except ZeroDivisionError:
            return float('nan')

    def global_mean_wrapper(self, question: str):
        """ Wraps the global_mean function to return a json string """
        dict_result = {"global_mean": self.global_mean(question)}
        return json.dumps(dict_result)

    def state_diff_from_mean(self, state: State, question: str):
        """ Computes the difference between the global mean of a question and a state mean """
        state_mean = self.mean_state(state, question)
        global_mean = self.global_mean(question)

        return global_mean - state_mean

    def state_diff_from_mean_wrapper(self, state_name: str, question: str):
        """ Wraps the state_diff_from_mean function to return a json string """
        dict_result = {state_name: self.state_diff_from_mean(self.states[state_name], question)}
        return json.dumps(dict_result)

    def diff_from_mean(self, question: str):
        """ Returns a list of the differences between the global mean and the
            state mean for a question """
        states = self.states.values()
        diffs = {}
        for state in states:
            if question not in state.question_to_rows:
                continue
            diffs[state.name] = self.state_diff_from_mean(state, question)

        return diffs

    def diff_from_mean_wrapper(self, question: str):
        """ Wraps the state_diffs_from_mean function to return a json string """
        return json.dumps(self.diff_from_mean(question))

    def state_mean_by_category(self, state: State, question: str):
        """ Calculate the mean of all categories for a state and a question"""
        result = {}
        for stratification, rows in state.question_to_stratification_to_rows[question].items():
            mean = 0.0
            length = 0.0

            for row in rows:
                value = row['Data_Value']
                try:
                    value = float(value)
                except ValueError:
                    continue

                mean += value
                length += 1.0

            try:
                result[stratification] = mean / length
            except ZeroDivisionError:
                result[stratification] = float('nan')

        return result

    def state_mean_by_category_wrapper(self, state_name: str, question: str):
        """ Wraps the state_mean_by_category function to return a json string """
        dict_result = self.state_mean_by_category(self.states[state_name], question)

        result = {}
        for key, value in dict_result.items():
            result[str(key)] = value

        return json.dumps({state_name: result})

    def mean_by_category(self, question: str):
        """ Calculate the mean of all categories for all states and a question """
        states = self.states.values()
        result = {}
        for state in states:
            if question not in state.question_to_stratification_to_rows:
                continue

            answers = self.state_mean_by_category(state, question)

            for (category, stratification), mean in answers.items():
                result[str((state.name, category, stratification))] = mean

        return result

    def mean_by_category_wrapper(self, question: str):
        """ Wraps the mean_by_category function to return a json string """
        return json.dumps(self.mean_by_category(question))
