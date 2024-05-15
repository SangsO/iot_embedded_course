package com.test.exam03;

interface Sales {

    public void manager();
    public void goal();
    public void product();

} // interface Sales_end

class ATeam implements Sales {

    @Override
    public void manager() {
        System.out.println("A팀장입니다. 열심히 하겠다.");
        }

    @Override
    public void goal() {
        System.out.println("A팀은 올해 70원 달성해보던지.");
        }

    @Override
    public void product() {
        System.out.println("A팀은 TV를 판매하겠습니다.");
    }    
} //class A1team implements Sales_end


class BTeam implements Sales {

    @Override
    public void manager() {
        System.out.println("B팀장입니다.");
              
    }

    @Override
    public void goal() {
        System.out.println("B팀은 올해 100원 달성.");
              
    }

    @Override
    public void product() {
        System.out.println("B팀은 콤퓨타 팔아보겠음");
            
    }
 
} //class Bteam implements Sales_end



public class InterfaceExam {

    public static void main(String[] args) {
        ATeam aSalesPlan = new ATeam();
        aSalesPlan.manager();
        aSalesPlan.goal();
        aSalesPlan.product();

        BTeam bSalesPlan = new BTeam();
        bSalesPlan.manager();
        bSalesPlan.goal();
        bSalesPlan.product();

    }
}

