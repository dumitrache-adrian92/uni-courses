package p4;

public class TwentyStrategy implements Strategy {
    @Override
    public float calcul(int aniVechime, float salariu) {
        float num = 20;
        return ((float)aniVechime / num) * salariu;
    }
}
