package p4;

public class ThirtyStrategy implements Strategy {
    @Override
    public float calcul(int aniVechime, float salariu) {
        float num = 30;
        return ((float)aniVechime / num) * salariu;
    }
}
