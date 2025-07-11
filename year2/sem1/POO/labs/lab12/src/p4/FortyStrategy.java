package p4;

public class FortyStrategy implements Strategy {
    @Override
    public float calcul(int aniVechime, float salariu) {
        float num = 40;
        return ((float)aniVechime / num) * salariu;
    }
}
