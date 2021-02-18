/**
 * This is the test class contains main
 */
public class TEST {
    public static void main(String args[])
    {
        GTUSet<Integer> testSet = new GTUSet<>();
        System.out.println("------TEST SET------");
        System.out.println("insert 2 3 5 6 7");
        testSet.insert(2);
        testSet.insert(3);
        testSet.insert(5);
        testSet.insert(6);
        testSet.insert(7);
        System.out.println("show elements using hasNext next iterator");
        GTUIterator iter = testSet.iterator();
        while (iter.hasNext())
        {
            System.out.println(iter.next());
        }
        System.out.println("erase 5");
        testSet.erase(5);
        GTUIterator iter1 = testSet.iterator();
        while (iter1.hasNext())
        {
            System.out.println(iter1.next());
        }
        System.out.println("\nsize is:");
        System.out.println(testSet.size());
        System.out.println();
        if(testSet.contains(0)){
            System.out.println("this collection contains 0");
        }
        System.out.println("max_size is:");
        System.out.println(testSet.max_size());
        System.out.println();
        System.out.println("clear set after check is it empty by empty method");
        testSet.clear();
        if(!testSet.empty())
            System.out.println("set is empty");


        GTUVector<Integer> testVector = new GTUVector<>();
        System.out.println("\n\n------TEST VECTOR------");
        System.out.println("insert 3 4 5 6");
        testVector.insert(3);
        testVector.insert(4);
        testVector.insert(5);
        testVector.insert(6);
        System.out.println("show elements using hasNext next iterator");
        GTUIterator iter3 = testVector.iterator();
        while (iter3.hasNext())
        {
            System.out.println(iter3.next());
        }
        System.out.println("erase 4");
        testVector.erase(4);
        GTUIterator iter4 = testVector.iterator();
        while (iter4.hasNext())
        {
            System.out.println(iter4.next());
        }
        System.out.println("\nsize is:");
        System.out.println(testVector.size());
        System.out.println();
        if(testVector.contains(0)){
            System.out.println("this collection contains 0");
        }
        System.out.println("max_size is:");
        System.out.println(testVector.max_size());
        System.out.println();
        System.out.println("clear vector after check is it empty by empty method");
        testVector.clear();
        if(!testVector.empty())
            System.out.println("vector is empty");
    }
}
