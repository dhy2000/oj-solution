import java.math.BigDecimal;
import java.math.MathContext;
import java.math.RoundingMode;
import java.util.ArrayList;
import java.util.Scanner;

public class Main {
    // 用 C++ 疑似被卡了浮点精度
    
    public static class Distance {
        public final BigDecimal dist;
        public final BigDecimal speed;

        Distance(double dist, double speed) {
            this.dist = BigDecimal.valueOf(dist);
            this.speed = BigDecimal.valueOf(speed);
        }

        BigDecimal getTime() {
            return getTime(BigDecimal.ZERO);
        }

        BigDecimal getTime(BigDecimal offset) {
            assert speed.add(offset).compareTo(BigDecimal.ZERO) > 0;
            return dist.divide(speed.add(offset), CTX);
        }
    }

    public static final MathContext CTX = new MathContext(20, RoundingMode.HALF_UP);
    public static final BigDecimal EPS = BigDecimal.valueOf(10).pow(-12, CTX);

    Main() {
        Scanner cin = new Scanner(System.in);
        while (cin.hasNext()) {
            int n = cin.nextInt();
            BigDecimal t = BigDecimal.valueOf(cin.nextDouble());
            ArrayList<Distance> distances = new ArrayList<>();
            BigDecimal sMin = BigDecimal.valueOf(1000);
            for (int i = 0; i < n; i++) {
                double d = cin.nextDouble();
                double s = cin.nextDouble();
                Distance dist = new Distance(d, s);
                distances.add(dist);
                if (sMin.compareTo(dist.speed) > 0) {
                    sMin = dist.speed;
                }
            }
            BigDecimal cMin = sMin.negate().add(EPS), cMax = BigDecimal.valueOf(10).pow(10);
            BigDecimal c = cMax;
            while (cMax.subtract(cMin).compareTo(EPS) > 0) {
                c = cMax.add(cMin).divide(BigDecimal.valueOf(2), CTX);
                BigDecimal tSum = BigDecimal.ZERO;
                for (Distance dist: distances) {
                    tSum = tSum.add(dist.getTime(c));
                }
                if (tSum.subtract(t).abs().compareTo(EPS) < 0) {
                    break;
                }
                else if (tSum.compareTo(t) > 0) {
                    cMin = c;
                }
                else {
                    cMax = c;
                }
            }
            System.out.println(c.round(CTX));
        }

        cin.close();
    }

    public static void main(String[] args) {
        new Main();
    }
}