package gc;

public class GC {

    public static void main(String[] args) throws InterruptedException {
        if (args.length != 3) {
            showHelp();
            System.exit(-1);
        }
        int elSize = Integer.parseInt(args[0]);
        int elCount = Integer.parseInt(args[1]);
        int allocCount = Integer.parseInt(args[2]);

        System.out.println("Element size: " + elSize);
        System.out.println("Element count: " + elCount);
        System.out.println("Allocation count: " + allocCount);

        long startTime = System.currentTimeMillis();
        doBenchmark(elSize, elCount, allocCount);
        long stopTime = System.currentTimeMillis();

        long execTime = stopTime - startTime;
        double seconds = execTime * 1.0 / 1000;
        double allocsPerSec = allocCount / seconds;
        double mbPerSec = (1L * allocCount * elSize / 1e6) / seconds;

        System.out.println("Time: " + seconds + " seconds");
        System.out.println("Allocations: " + allocsPerSec + " allocations per second");
        System.out.println("Allocations: " + mbPerSec + " MB/s");
    }

    private static void showHelp() {
        System.err.println(
                "java "
                + GC.class.getName()
                + " element_size element_count allocation_count");
    }

    private static void doBenchmark(
            int elSize,
            int elCount,
            int allocCount)
            throws InterruptedException {
        byte[][] elements = new byte[elCount][];

        for (int i = 0; i < allocCount; i++) {
            int slot = i % elCount;
            elements[slot] = new byte[elSize];
            for (int j = 0; j < elSize; j++) {
                elements[slot][j] = (byte) i;
            }
        }

        long tot = 0l;
        for (byte[] element : elements) {
            if (element != null) {
                for (byte b : element) {
                    tot += b;
                }
            }
        }

        System.out.println("Sum: " + tot);

        System.gc();
    }
}
