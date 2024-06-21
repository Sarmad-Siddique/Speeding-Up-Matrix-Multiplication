import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public class matrixmul_java {
    public static void main(String[] args) {
        if (args.length != 2) {
            System.out.println("2 command line arguments are expected to run the code. Exiting the code.");
            return;
        }

        String input_file = args[0];
        String output_file = args[1];

        try {
            BufferedReader br = new BufferedReader(new FileReader(input_file));

            int programtype = 0;
            int datatype = 0;

            programtype = Integer.parseInt(br.readLine());
            datatype = Integer.parseInt(br.readLine());

            System.out.println("ProgramType: " + programtype);
            System.out.println("Data Type: " + datatype);

            switch (datatype) {
                case 1:
                    Run_32BitInt(input_file, output_file);
                    break;
                case 2:
                    Run_32BitFloat(input_file, output_file);
                    break;
                case 3:
                    Run_64BitInt(input_file, output_file);
                    break;
                case 4:
                    Run_64BitDouble(input_file, output_file);
                    break;
                default:
                    System.out.println("Invalid data type OpCode, Halting execution");
            }

            br.close();

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void Run_32BitInt(String input_file, String output_file) {
        try {
            BufferedReader br = new BufferedReader(new FileReader(input_file));

            int programtype = 0;
            int datatype = 0;
            int dimension1 = 0, dimension2 = 0;
            char garbage;

            programtype = Integer.parseInt(br.readLine());
            datatype = Integer.parseInt(br.readLine());
            String[] dimensions = br.readLine().split("X");
            dimension1 = Integer.parseInt(dimensions[0]);
            dimension2 = Integer.parseInt(dimensions[1]);

            if (dimension1 != 4096 || dimension2 != 4096) {
                System.out.println("Invalid Dimensions given for matrix 1");
                System.out.println("Dimension 1: " + dimension1);
                System.out.println("Dimension 2: " + dimension2);
                br.close();
                return;
            }

            int[][] matrix1 = new int[4096][4096];
            int[][] matrix2 = new int[4096][4096];
            int[][] matrix3 = new int[4096][4096];

            for (int i = 0; i < 4096; i++) {
                String[] row = br.readLine().split(" ");
                for (int j = 0; j < 4096; j++) {
                    matrix1[i][j] = Integer.parseInt(row[j]);
                }
            }

            dimensions = br.readLine().split("X");
            dimension1 = Integer.parseInt(dimensions[0]);
            dimension2 = Integer.parseInt(dimensions[1]);

            if (dimension1 != 4096 || dimension2 != 4096) {
                System.out.println("Invalid Dimensions given for matrix 2");
                System.out.println("Dimension 1: " + dimension1);
                System.out.println("Dimension 2: " + dimension2);
                br.close();
                return;
            }

            for (int i = 0; i < 4096; i++) {
                String[] row = br.readLine().split(" ");
                for (int j = 0; j < 4096; j++) {
                    matrix2[i][j] = Integer.parseInt(row[j]);
                }
            }

            br.close();

            long seconds_start;
            long seconds_finish;

            seconds_start = System.currentTimeMillis();

            for (int i = 0; i < 4096; i++) {
                for (int j = 0; j < 4096; j++) {
                    for (int k = 0; k < 4096; k++) {
                        matrix3[i][j] += matrix1[i][k] * matrix2[k][j];
                    }
                }
            }

            seconds_finish = System.currentTimeMillis();

            System.out.println("Time taken for calculations = " + (seconds_finish - seconds_start));

            FileWriter fw = new FileWriter(output_file);
            fw.write("1\n4096X4096\n");

            for (int i = 0; i < 4096; i++) {
                for (int j = 0; j < 4096; j++) {
                    fw.write(matrix3[i][j] + " ");
                }
                fw.write("\n");
            }

            fw.close();

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void Run_64BitInt(String input_file, String output_file) {
        try {
            BufferedReader br = new BufferedReader(new FileReader(input_file));

            int programtype = 0;
            int datatype = 0;
            int dimension1 = 0, dimension2 = 0;
            char garbage;

            programtype = Integer.parseInt(br.readLine());
            datatype = Integer.parseInt(br.readLine());
            String[] dimensions = br.readLine().split("X");
            dimension1 = Integer.parseInt(dimensions[0]);
            dimension2 = Integer.parseInt(dimensions[1]);

            if (dimension1 != 4096 || dimension2 != 4096) {
                System.out.println("Invalid Dimensions given for matrix 1");
                System.out.println("Dimension 1: " + dimension1);
                System.out.println("Dimension 2: " + dimension2);
                br.close();
                return;
            }

            long[][] matrix1 = new long[4096][4096];
            long[][] matrix2 = new long[4096][4096];
            long[][] matrix3 = new long[4096][4096];

            for (int i = 0; i < 4096; i++) {
                String[] row = br.readLine().split(" ");
                for (int j = 0; j < 4096; j++) {
                    matrix1[i][j] = Long.parseLong(row[j]);
                }
            }

            dimensions = br.readLine().split("X");
            dimension1 = Integer.parseInt(dimensions[0]);
            dimension2 = Integer.parseInt(dimensions[1]);

            if (dimension1 != 4096 || dimension2 != 4096) {
                System.out.println("Invalid Dimensions given for matrix 2");
                System.out.println("Dimension 1: " + dimension1);
                System.out.println("Dimension 2: " + dimension2);
                br.close();
                return;
            }

            for (int i = 0; i < 4096; i++) {
                String[] row = br.readLine().split(" ");
                for (int j = 0; j < 4096; j++) {
                    matrix2[i][j] = Long.parseLong(row[j]);
                }
            }

            br.close();

            long seconds_start;
            long seconds_finish;

            seconds_start = System.currentTimeMillis();

            for (int i = 0; i < 4096; i++) {
                for (int j = 0; j < 4096; j++) {
                    for (int k = 0; k < 4096; k++) {
                        matrix3[i][j] += matrix1[i][k] * matrix2[k][j];
                    }
                }
            }

            seconds_finish = System.currentTimeMillis();

            System.out.println("Time taken for calculations = " + (seconds_finish - seconds_start));

            FileWriter fw = new FileWriter(output_file);
            fw.write("1\n4096X4096\n");

            for (int i = 0; i < 4096; i++) {
                for (int j = 0; j < 4096; j++) {
                    fw.write(matrix3[i][j] + " ");
                }
                fw.write("\n");
            }

            fw.close();

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    
    public static void Run_64BitDouble(String input_file, String output_file) {
        try {
            BufferedReader br = new BufferedReader(new FileReader(input_file));

            int programtype = 0;
            int datatype = 0;
            int dimension1 = 0, dimension2 = 0;
            char garbage;

            programtype = Integer.parseInt(br.readLine());
            datatype = Integer.parseInt(br.readLine());
            String[] dimensions = br.readLine().split("X");
            dimension1 = Integer.parseInt(dimensions[0]);
            dimension2 = Integer.parseInt(dimensions[1]);

            if (dimension1 != 4096 || dimension2 != 4096) {
                System.out.println("Invalid Dimensions given for matrix 1");
                System.out.println("Dimension 1: " + dimension1);
                System.out.println("Dimension 2: " + dimension2);
                br.close();
                return;
            }

            double[][] matrix1 = new double[4096][4096];
            double[][] matrix2 = new double[4096][4096];
            double[][] matrix3 = new double[4096][4096];

            for (int i = 0; i < 4096; i++) {
                String[] row = br.readLine().split(" ");
                for (int j = 0; j < 4096; j++) {
                    matrix1[i][j] = Double.parseDouble(row[j]);
                }
            }

            dimensions = br.readLine().split("X");
            dimension1 = Integer.parseInt(dimensions[0]);
            dimension2 = Integer.parseInt(dimensions[1]);

            if (dimension1 != 4096 || dimension2 != 4096) {
                System.out.println("Invalid Dimensions given for matrix 2");
                System.out.println("Dimension 1: " + dimension1);
                System.out.println("Dimension 2: " + dimension2);
                br.close();
                return;
            }

            for (int i = 0; i < 4096; i++) {
                String[] row = br.readLine().split(" ");
                for (int j = 0; j < 4096; j++) {
                    matrix2[i][j] = Double.parseDouble(row[j]);
                }
            }

            br.close();

            long seconds_start;
            long seconds_finish;

            seconds_start = System.currentTimeMillis();

            for (int i = 0; i < 4096; i++) {
                for (int j = 0; j < 4096; j++) {
                    for (int k = 0; k < 4096; k++) {
                        matrix3[i][j] += matrix1[i][k] * matrix2[k][j];
                    }
                }
            }

            seconds_finish = System.currentTimeMillis();

            System.out.println("Time taken for calculations = " + (seconds_finish - seconds_start));

            FileWriter fw = new FileWriter(output_file);
            fw.write("1\n4096X4096\n");

            for (int i = 0; i < 4096; i++) {
                for (int j = 0; j < 4096; j++) {
                    fw.write(matrix3[i][j] + " ");
                }
                fw.write("\n");
            }

            fw.close();

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    
    public static void Run_32BitFloat(String input_file, String output_file) {
        try {
            BufferedReader br = new BufferedReader(new FileReader(input_file));

            int programtype = 0;
            int datatype = 0;
            int dimension1 = 0, dimension2 = 0;
            char garbage;

            programtype = Integer.parseInt(br.readLine());
            datatype = Integer.parseInt(br.readLine());
            String[] dimensions = br.readLine().split("X");
            dimension1 = Integer.parseInt(dimensions[0]);
            dimension2 = Integer.parseInt(dimensions[1]);

            if (dimension1 != 4096 || dimension2 != 4096) {
                System.out.println("Invalid Dimensions given for matrix 1");
                System.out.println("Dimension 1: " + dimension1);
                System.out.println("Dimension 2: " + dimension2);
                br.close();
                return;
            }

            float[][] matrix1 = new float[4096][4096];
            float[][] matrix2 = new float[4096][4096];
            float[][] matrix3 = new float[4096][4096];

            for (int i = 0; i < 4096; i++) {
                String[] row = br.readLine().split(" ");
                for (int j = 0; j < 4096; j++) {
                    matrix1[i][j] = Float.parseFloat(row[j]);
                }
            }

            dimensions = br.readLine().split("X");
            dimension1 = Integer.parseInt(dimensions[0]);
            dimension2 = Integer.parseInt(dimensions[1]);

            if (dimension1 != 4096 || dimension2 != 4096) {
                System.out.println("Invalid Dimensions given for matrix 2");
                System.out.println("Dimension 1: " + dimension1);
                System.out.println("Dimension 2: " + dimension2);
                br.close();
                return;
            }

            for (int i = 0; i < 4096; i++) {
                String[] row = br.readLine().split(" ");
                for (int j = 0; j < 4096; j++) {
                    matrix2[i][j] = Float.parseFloat(row[j]);
                }
            }

            br.close();

            long seconds_start;
            long seconds_finish;

            seconds_start = System.currentTimeMillis();

            for (int i = 0; i < 4096; i++) {
                for (int j = 0; j < 4096; j++) {
                    for (int k = 0; k < 4096; k++) {
                        matrix3[i][j] += matrix1[i][k] * matrix2[k][j];
                    }
                }
            }

            seconds_finish = System.currentTimeMillis();

            System.out.println("Time taken for calculations = " + (seconds_finish - seconds_start));

            FileWriter fw = new FileWriter(output_file);
            fw.write("1\n4096X4096\n");

            for (int i = 0; i < 4096; i++) {
                for (int j = 0; j < 4096; j++) {
                    fw.write(matrix3[i][j] + " ");
                }
                fw.write("\n");
            }

            fw.close();

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    
}

