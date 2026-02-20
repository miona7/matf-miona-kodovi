package quiz;

import java.util.ArrayList;
import java.util.List;

public class Session {
    private Question currentQuestion;
    private List<Question> questionsToBeAnswered;

    Session(List<Question> questionsToBeAnswered) {
        this.questionsToBeAnswered = new ArrayList<>(questionsToBeAnswered);
    }

    public Question getCurrentQuestion() {
        return currentQuestion;
    }

    public void setCurrentQuestion(Question currentQuestion) {
        this.currentQuestion = currentQuestion;
    }

    public boolean hasNextQuestion() {
        return !questionsToBeAnswered.isEmpty();
    }

    public Question getNextQuestion() {
        return questionsToBeAnswered.remove(0);
    }
}
