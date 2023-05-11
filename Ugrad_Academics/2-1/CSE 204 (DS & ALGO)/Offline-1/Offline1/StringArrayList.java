package Offline1;

public class StringArrayList {

    private String[] stringArray;
    private int length;

   public StringArrayList()
    {
        length=0;
        this.stringArray=new String[length];
    }

   public StringArrayList(int n)
    {
        length=n;
        this.stringArray=new String[length];

    }

    public StringArrayList(String[] arr)
    {
        length=arr.length;
        this.stringArray=arr;
    }


    public StringArrayList getArray()
    {
        return this;
    }

    public int Length()
    {
        return length;
    }


    public String getAnElement(int i)
    {
        if(i<0 || i>=length)
        {
            System.out.println("Invalid index input");
            return null;
        }

        return this.stringArray[i];
    }

    public void add(String str)
    {
        //updating the length

        this.length=this.length+1;
        String[] temp=new String[this.length];

        //copying the existing element of stringArray in temp
        for (int i=0;i<length-1;i++)
        {
            temp[i]=this.stringArray[i];
        }
        temp[length-1]=str;
        this.stringArray=temp;

    }

    public void add(int i,String str)
    {
        //updating the length

        if(i<0 || i > length)
        {
            System.out.println("index out of bound");
            return;
        }

        this.length=this.length+1;
        String[] temp=new String[this.length];



        for (int c=0;c<i;c++)
        {
            temp[c]=this.stringArray[c];
        }
        temp[i]=str;
        for (int c=i;c<this.length-1;c++)
        {
            temp[c+1]=this.stringArray[c];
        }
        this.stringArray=temp;

    }

    public void remove(String str)
    {

       // int[] removingIndex=new int[this.length];

        //the number of removing element is storing in RemovingCount
        int RemovingCount=0;

        for (int i=0;i<this.length;i++)
        {
            if(this.stringArray[i].equalsIgnoreCase(str))
            {
               // removingIndex[RemovingCount]=i;
                stringArray[i]=null;
                RemovingCount++;
            }
        }

        if(RemovingCount==0)
        {
            System.out.println("There is no string "+"\""+str+"\"" +" in the list");
        }
        else
        {
            int oldLength=this.length;
            //updating the length
            this.length=this.length-RemovingCount;
            String[] temp=new String[this.length];
            int realIndex=0;
            for (int i=0;i<oldLength;i++)
            {
                if(stringArray[i]==null)
                    continue;
                temp[realIndex]=stringArray[i];
                realIndex++;

            }
            stringArray=temp;

        }

    }

    public int[] findIndex(String str)
    {

        int countOccurance=0;

        //at first counting the occurance of str in the list
        for(int i=0;i<this.length;i++)
        {
            if(this.stringArray[i].equalsIgnoreCase(str))
            {
                countOccurance++;
            }
        }

        if(countOccurance==0)
        {
            System.out.println("the string "+"\""+str+"\"" +" does not exist in the list");
            return null;
        }

        else
        {
            //finding all the indexes and storing them in an array
            int[] Allindex=new int[countOccurance];
            int countIndex=0;

            for(int i=0;i<this.length;i++)
            {
                if(this.stringArray[i].equals(str))
                {
                    Allindex[countIndex]=i;
                    countIndex++;
                }
            }

            return Allindex;

        }


    }

    //assuming end exclusive
    public StringArrayList subArray(int start,int end)
    {
        if(start < 0 || end >length || end - start < 0)
        {
            System.out.println("Invalid indexing input");
            return null;
        }
        else
        {
            String[] temp=new String[end-start];
            int index=0;
            for (int i=start;i<end;i++)
            {
                temp[index]=stringArray[i];
                index++;
            }

            return new StringArrayList(temp);
        }
    }

    public StringArrayList merge(String[] arr1,String[] arr2)
    {
        this.length=arr1.length+arr2.length;
        this.stringArray=new String[this.length];
        int index=0;

        for(int i=0;i<arr1.length;i++)
        {
            stringArray[index]=arr1[i];
            index++;
        }

        for(int i=0;i<arr2.length;i++)
        {
            stringArray[index]=arr2[i];
            index++;
        }

        //sorting the final list

        String temp;
        for(int c=0;c<this.length-1;c++)
        {
            for(int k=c+1;k<this.length;k++)
            {
                if(stringArray[c].compareToIgnoreCase(stringArray[k])>0)
                {
                    temp=stringArray[c];
                    stringArray[c]=stringArray[k];
                    stringArray[k]=temp;

                }
            }
        }

        return this;

    }


    public boolean isEmpty()
    {
        if(this.length==0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    @Override
    public String toString() {
        String str="[";
        for(int i=0;i<this.length;i++)
        {
           str=str+stringArray[i];
           if(i!=this.length-1)
           {
               str=str+",";
           }

        }
        str=str+"]";

        return str;
    }
}

class Main
{
    public static void main(String[] args) {

        StringArrayList stringArrayList=new StringArrayList();
        stringArrayList.add("Fahim");
        stringArrayList.add("Farhan");
        System.out.println(stringArrayList);
        stringArrayList.add("ADFF");
        stringArrayList.add("Fahim");
        System.out.println(stringArrayList);
        System.out.println(stringArrayList.Length());

        stringArrayList.add(1,"DFRE");
        System.out.print("After adding "+"\""+"DFRE"+"\"" +" at index 1: ");
        System.out.println(stringArrayList);
        stringArrayList.add(5,"Fahims");
        System.out.print("After adding "+"\""+"Fahims"+"\"" +" at index 5: ");

        System.out.println(stringArrayList);
        stringArrayList.remove("Fahims");
        System.out.print("After removing "+"\""+"Fahims"+"\""+" :");
        System.out.println(stringArrayList);
        int[] arr=stringArrayList.findIndex("DFRE");

        if(arr !=null)

        {
            System.out.print("Index of "+"\""+"DFRE"+"\""+" :" );
            for (int x:arr)
        {
            System.out.print(x+" ");
        }
        }

        System.out.println();



        String[] strings1={"A","B","C","P","Q","Y","Z"};
        String[] strings2={"D","F","G","H"};
        System.out.print("After Mergirg: ");
        stringArrayList.merge(strings1,strings2);
        System.out.println(stringArrayList.getArray());
        System.out.print("After merging the length is: ");
        System.out.println(stringArrayList.Length());

        System.out.println("The subarray between 1 and 8 is: ");
        System.out.println(stringArrayList.subArray(1,8));


    }
}
