package Grade_Testing;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class Grading_Calculation_Test {


//credit 3

    @Test
    void Mark_400_should_get_A_in_Credit_3()
    {
        Grading grading = new Grading();
        assertEquals('A',grading.get_grade(3,400));
    }


    @Test
    void Mark_350_should_get_A_in_Credit_3()
    {
        Grading grading = new Grading();
        assertEquals('A',grading.get_grade(3,350));
    }

    @Test
    void Mark_240_should_get_A_in_Credit_3()
    {
        Grading grading = new Grading();
        assertEquals('A',grading.get_grade(3,240));
    }

    @Test
    void Mark_239_point_6_should_get_A_in_Credit_3()
    {
        Grading grading = new Grading();
        assertEquals('A',grading.get_grade(3,239.6));
    }

    @Test
    void Mark_239_point_1_should_get_A_in_Credit_3()
    {
        Grading grading = new Grading();
        assertEquals('A',grading.get_grade(3,239.1));
    }


    @Test
    void Mark_239_should_get_B_in_Credit_3()
    {
        Grading grading = new Grading();
        assertEquals('B',grading.get_grade(3,239));
    }

    @Test
    void Mark_230_should_get_B_in_Credit_3()
    {
        Grading grading = new Grading();
        assertEquals('B',grading.get_grade(3,230));
    }


    @Test
    void Mark_210_should_get_B_in_Credit_3()
    {
        Grading grading = new Grading();
        assertEquals('B',grading.get_grade(3,210));
    }
    @Test
    void Mark_209_point_5_should_get_B_in_Credit_3()
    {
        Grading grading = new Grading();
        assertEquals('B',grading.get_grade(3,209.5));
    }
    @Test
    void Mark_209_point_2_should_get_B_in_Credit_3()
    {
        Grading grading = new Grading();
        assertEquals('B',grading.get_grade(3,209.2));
    }

    @Test
    void Mark_209_should_get_C_in_Credit_3()
    {
        Grading grading = new Grading();
        assertEquals('C',grading.get_grade(3,209));
    }


    @Test
    void Mark_190_should_get_C_in_Credit_3()
    {
        Grading grading = new Grading();
        assertEquals('C',grading.get_grade(3,190));
    }

    @Test
    void Mark_180_should_get_C_in_Credit_3()
    {
        Grading grading = new Grading();
        assertEquals('C',grading.get_grade(3,180));
    }
    @Test
    void Mark_179_point_8_should_get_C_in_Credit_3()
    {
        Grading grading = new Grading();
        assertEquals('C',grading.get_grade(3,179.8));
    }
    @Test
    void Mark_179_point_3_should_get_C_in_Credit_3()
    {
        Grading grading = new Grading();
        assertEquals('C',grading.get_grade(3,179.3));
    }
    @Test
    void Mark_179_should_get_F_in_Credit_3()
    {
        Grading grading = new Grading();
        assertEquals('F',grading.get_grade(3,179));
    }


    @Test
    void Mark_150_should_get_F_in_Credit_3()
    {
        Grading grading = new Grading();
        assertEquals('F',grading.get_grade(3,150));
    }


    @Test
    void Mark_0_should_get_F_in_Credit_3()
    {
        Grading grading = new Grading();
        assertEquals('F',grading.get_grade(3,0));
    }


    //credit 4
    @Test
    void Mark_400_should_get_A_in_Credit_4()
    {
        Grading grading = new Grading();
        assertEquals('A',grading.get_grade(4,400));
    }
    @Test
    void Mark_370_should_get_A_in_Credit_4()
    {
        Grading grading = new Grading();
        assertEquals('A',grading.get_grade(4,370));
    }

    @Test
    void Mark_320_should_get_A_in_Credit_4()
    {
        Grading grading = new Grading();
        assertEquals('A',grading.get_grade(4,320));
    }
    @Test
    void Mark_319_point_6_should_get_A_in_Credit_4()
    {
        Grading grading = new Grading();
        assertEquals('A',grading.get_grade(4,319.6));
    }
    @Test
    void Mark_319_point_1_should_get_A_in_Credit_4()
    {
        Grading grading = new Grading();
        assertEquals('A',grading.get_grade(4,319.1));
    }
    @Test
    void Mark_319_should_get_B_in_Credit_4()
    {
        Grading grading = new Grading();
        assertEquals('B',grading.get_grade(4,319));
    }
    @Test
    void Mark_310_should_get_B_in_Credit_4()
    {
        Grading grading = new Grading();
        assertEquals('B',grading.get_grade(4,310));
    }

    @Test
    void Mark_280_should_get_B_in_Credit_4()
    {
        Grading grading = new Grading();
        assertEquals('B',grading.get_grade(4,280));
    }
    @Test
    void Mark_279_point_6_should_get_B_in_Credit_4()
    {
        Grading grading = new Grading();
        assertEquals('B',grading.get_grade(4,279.6));
    }
    @Test
    void Mark_279_point_4_should_get_B_in_Credit_4()
    {
        Grading grading = new Grading();
        assertEquals('B',grading.get_grade(4,279.4));
    }

    @Test
    void Mark_279_should_get_C_in_Credit_4()
    {
        Grading grading = new Grading();
        assertEquals('C',grading.get_grade(4,279));
    }

    @Test
    void Mark_255_should_get_C_in_Credit_4()
    {
        Grading grading = new Grading();
        assertEquals('C',grading.get_grade(4,255));
    }

    @Test
    void Mark_240_should_get_C_in_Credit_4()
    {
        Grading grading = new Grading();
        assertEquals('C',grading.get_grade(4,240));
    }
    @Test
    void Mark_239_point_7_should_get_C_in_Credit_4()
    {
        Grading grading = new Grading();
        assertEquals('C',grading.get_grade(4,239.7));
    }
    @Test
    void Mark_239_point_1_should_get_C_in_Credit_4()
    {
        Grading grading = new Grading();
        assertEquals('C',grading.get_grade(4,239.1));
    }

    @Test
    void Mark_239_should_get_F_in_Credit_4()
    {
        Grading grading = new Grading();
        assertEquals('F',grading.get_grade(4,239));
    }

    @Test
    void Mark_200_should_get_F_in_Credit_4()
    {
        Grading grading = new Grading();
        assertEquals('F',grading.get_grade(4,200));
    }

    @Test
    void Mark_0_should_get_F_in_Credit_4()
    {
        Grading grading = new Grading();
        assertEquals('F',grading.get_grade(4,0));
    }


    //invalid mark for both credit 3 and 4 (negative or greater than 400)
    @Test
    void Mark_Minus_10_should_get_error_in_Credit_3()
    {
        Grading grading = new Grading();
        assertThrows(IllegalArgumentException.class,()->{
            System.out.println("Invalid Input ! Mark can't be negative");
            grading.get_grade(3,-10);
        });
    }
    @Test
    void Mark_Minus_0_point_5_should_get_error_in_Credit_4()
    {
        Grading grading = new Grading();
        assertThrows(IllegalArgumentException.class,()->{
            System.out.println("Invalid Input ! Mark can't be negative");
            grading.get_grade(4,-0.5);
        });
    }
   @Test
    void Mark_1000_should_get_error_in_Credit_3()
    {
        Grading grading = new Grading();
        assertThrows(IllegalArgumentException.class,()->{
            System.out.println("Invalid Input ! Highest mark is 400");
            grading.get_grade(3,1000);
        });
    }
    @Test
    void Mark_400_point_01_should_get_error_in_Credit_4()
    {
        Grading grading = new Grading();
        assertThrows(IllegalArgumentException.class,()->{
            System.out.println("Invalid Input ! Highest mark is 400");
            grading.get_grade(4,400.01);
        });
    }

    //invalid credit input
    @Test
    void Invalid_Credit_input_test()
    {
        Grading grading = new Grading();
        assertThrows(IllegalArgumentException.class,()->{
            System.out.println("Invalid input ! Credit should be either 3 or 4");
            grading.get_grade(3.5,350);
        });
    }

    //Non number input testing
    @Test
    void Non_Number_input_test1()
    {
        Grading grading = new Grading();
        assertThrows(NumberFormatException.class,()->{
            System.out.println("Invalid input ! Inputs should be Number");
            grading.get_grade("abc",250);
        });
    }
    @Test
    void Non_Number_input_test2()
    {
        Grading grading = new Grading();
        assertThrows(NumberFormatException.class,()->{
            System.out.println("Invalid input ! Inputs should be Number");
            grading.get_grade(3,"abc");
        });
    }
    @Test
    void Non_Number_input_test3()
    {
        Grading grading = new Grading();
        assertThrows(NumberFormatException.class,()->{
            System.out.println("Invalid input ! Inputs should be Number");
            grading.get_grade("abc","abc");
        });
    }






}