package Grade_Testing;

public class Grading {

    public char get_grade(Object cred,Object marks) {
        //Rounding the mark to the next integer value
        double rounded_mark = 0.0;

        double mark = 0.0;
        double credit = 0.0;

        if (cred instanceof Number && marks instanceof Number) {

            if (cred instanceof Double && marks instanceof Double) {
                credit = (double) cred;
                mark = (double) marks;
            } else if (cred instanceof Double && marks instanceof Integer) {
                credit = (double) cred;
                mark = (int) marks;
            } else if (cred instanceof Integer && marks instanceof Double) {
                credit = (int) cred;
                mark = (double) marks;
            } else if (cred instanceof Integer && marks instanceof Integer) {
                credit = (int) cred;
                mark = (int) marks;
            }
            //double mark = Double.parseDouble(marks);
            //double credit = Double.parseDouble(cred);

            if ((credit == 3.0 || credit == 4.0) && (mark >= 0 && mark <= 400)) {
                if ((Math.round(mark) - mark) < 0) {
                    rounded_mark = Math.round(mark) + 1;
                } else {
                    rounded_mark = Math.round(mark);
                }


                if (credit == 3.0) {
                    if (rounded_mark >= 240 && rounded_mark <= 400) {
                        return 'A';
                    } else if (rounded_mark >= 210 && rounded_mark <= 239) {
                        return 'B';
                    } else if (rounded_mark >= 180 && rounded_mark <= 209) {
                        return 'C';
                    } else if (rounded_mark < 180) {
                        return 'F';
                    }

                } else if (credit == 4.0) {
                    if (rounded_mark >= 320 && rounded_mark <= 400) {
                        return 'A';
                    } else if (rounded_mark >= 280 && rounded_mark <= 319) {
                        return 'B';
                    } else if (rounded_mark >= 240 && rounded_mark <= 279) {
                        return 'C';
                    } else if (rounded_mark < 240) {
                        return 'F';
                    }

                }


            } else {
                //invalid credit or out of range mark given
                if (!(credit == 3 || credit == 4)) {
                    throw new IllegalArgumentException("Invalid input ! Credit should be either 3 or 4");
                } else if (mark < 0) {
                    throw new IllegalArgumentException("Invalid Input ! Mark can't be negative ");
                } else if (mark > 400) {
                    throw new IllegalArgumentException("Invalid Input ! Highest mark is 400");
                }

                return 'N'; //N for invalid input
            }

            return 'N';
        }

        //if non number input given
        else
        {
            throw new NumberFormatException();
        }
    }



  /* public static void main(String[] args) {

        Grading grading = new Grading();


       System.out.println(grading.get_grade(3,1));


    }*/

}
