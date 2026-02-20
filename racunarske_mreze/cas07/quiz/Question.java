package quiz;

public class Question {
    private final String question;
    private final String answer;

    Question(String question, String answer) {
        this.question = question;
        this.answer = answer;
    }

    public String getQuestion() {
        return question;
    }

    public boolean checkAnswer(String answer) {
        return answer.equalsIgnoreCase(this.answer);
    }

    @Override
    public String toString() {
        return question + ": " + answer;
    }
}
