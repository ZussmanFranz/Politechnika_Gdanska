import numpy as np
from rl_base import Agent, Action, State
import os


class QAgent(Agent):

    def __init__(self, n_states, n_actions,
                 name='QAgent', initial_q_value=0.0, q_table=None):
        super().__init__(name)

        # hyperparams
        # TODO ustaw te parametry na sensowne wartości
        self.lr = 0.1              # współczynnik uczenia (learning rate)
        self.gamma = 0.9            # współczynnik dyskontowania
        self.epsilon = 0.01           # epsilon (p-wo akcji losowej)
        self.eps_decrement = 0.000001     # wartość, o którą zmniejsza się epsilon po każdym kroku
        self.eps_min = 0.005           # końcowa wartość epsilon, poniżej którego już nie jest zmniejszane

        self.action_space = [i for i in range(n_actions)]
        self.n_states = n_states
        self.q_table = q_table if q_table is not None else self.init_q_table(initial_q_value)

    def init_q_table(self, initial_q_value=0.):
        # TODO - utwórz tablicę wartości Q o rozmiarze [n_states, n_actions] wypełnioną początkowo wartościami initial_q_value
        q_table = np.full((self.n_states, len(self.action_space)), initial_q_value)
        return q_table

    def update_action_policy(self) -> None:
        # TODO - zaktualizuj wartość epsilon
        self.epsilon = max(self.epsilon - self.eps_decrement, self.eps_min)

    def choose_action(self, state: State) -> Action:

        assert 0 <= state < self.n_states, \
            f"Bad state_idx. Has to be int between 0 and {self.n_states}"

        # TODO - zaimplementuj strategię eps-zachłanną

        r = np.random.rand()

        if (r > self.epsilon):
            # greed choice (exploitation)
            return np.argmax(self.q_table[state])
        else:
            # random choice (exploration)
            return np.random.choice(self.action_space)

        return Action(0)  # na razie agent zawsze wybiera akcję "idź do góry"


    def learn(self, state: State, action: Action, reward: float, new_state: State, done: bool) -> None:
        # TODO - zaktualizuj q_table
        best_next_Q = np.max(self.q_table[new_state])
        theta = reward + self.gamma * best_next_Q - self.q_table[state, action]
        self.q_table[state, action] += self.lr * theta


    def save(self, path):
        os.makedirs(os.path.dirname(path), exist_ok=True)
        np.save(path, self.q_table)

    def load(self, path):
        self.q_table = np.load(path)

    def get_instruction_string(self):
        return [f"Linearly decreasing eps-greedy: eps={self.epsilon:0.4f}"]
