import java.util.*;
public class GramarAnalyser{
 
    static class Node{
        String value;
        ArrayList<Node> array;

        public Node(String value){
            this.value=value;
            array = new ArrayList<>();
        }
    }

    public static void main(String[] args){
        /*String a = "<S>::=<Aba>|<B> \
                  <A> ::= a ...>";*/
        Map<String, String[]> cfg = new HashMap<>();
        cfg.put("S",new String[] {"A","B"});
        cfg.put("A",new String[] {"a"});
        cfg.put("C",new String[] {"c",});
        cfg.put("B",new String[] {"Bb"});
        System.out.println("Initial cfg is: (Starting from S)");
        for(String key: cfg.keySet()){
            System.out.print(key+ "-> ");
            for(String production: cfg.get(key)){
                System.out.print(production+" ");
            }
            System.out.println();
         }
       
      
        Map<String,Node> nodes = reduceCFG(cfg);
        Map<String,String[]> used= eliminateU(nodes,cfg);
        System.out.println("No terminals that can be reached are: ");
        for(String key: used.keySet()){
           System.out.println(key);
        }
        Map<String,String[]> finalcfg = eliminateNoDerivable(used);
        System.out.println("The final cfg is: (Starting from S)");
        for(String key: finalcfg.keySet()){
            System.out.print(key+ "-> ");
            for(String production: finalcfg.get(key)){
                System.out.print(production+" ");
            }
            System.out.println();
         }

    }

    public static boolean reachable(Node node, Node terminal){
        Queue<Node> q = new LinkedList<>(); 
        q.add(node);
        HashSet<Node> h = new HashSet<>();
        h.add(node);
        while(!q.isEmpty()){
            Node current = q.poll();
            if(current == terminal){
                return true;
            }
            for(Node production: current.array){
                if(!h.contains(production)){
                    q.add(production);
                    h.add(production);
                } 
            }
        }
        return false;
    }

    public static Map<String,String[]> eliminateNoDerivable(Map<String,String[]> cfg){
        Map<String,Node> nodes = new   HashMap<String,Node>();
        boolean onlyT;
        Node terminal = new Node(null);
        for(String key: cfg.keySet()){
            nodes.put(key,new Node(key));
        }
        for(String key: cfg.keySet()){
           for(String production: cfg.get(key)){
               onlyT= true;
               for(int i=0;i<production.length();i++){
                   if(cfg.containsKey(production.charAt(i)+"")){
                       onlyT= false;
                       nodes.get(key).array.add(nodes.get(production.charAt(i)+""));
                   }
               }
               if(onlyT){
                nodes.get(key).array.add(terminal);
               }
           }
        }
        HashSet<String> removeInf = new HashSet<>();
        Map<String,String[]> newcfg = new HashMap<String,String[]>();
        for(String key: nodes.keySet()){
            if(reachable(nodes.get(key),terminal)){
                newcfg.put(key,cfg.get(key));
            }
            else{
                removeInf.add(key);
            }
        }

        newcfg = removeUseless(newcfg,removeInf);
        System.out.println("Productions that cant derive in a valid grammar:");
        System.out.println(removeInf);

        return newcfg;

    }

    public static Map<String,String[]>  removeUseless(Map<String,String[]> newcfg,  HashSet<String> removeInf){
        for(String key: newcfg.keySet()){
            for(String production: newcfg.get(key)){
                for(int i=0;i<production.length();i++){
                    if(removeInf.contains(production.charAt(i)+"")){
                        String[] inter= newcfg.get(key);
                        String[] newArray= removeElement(inter,production);
                        newcfg.put(key,newArray);
                    }
                }
            }
        }
        return newcfg;
    }

    public static String[] removeElement(String[] inter,String production){
        String[] result = new String[inter.length-1];
        int j=0;
        for(int i=0; i<inter.length;i++){
            if(!inter[i].equals(production)){
                result[j]=inter[i];
                j++;
            }
        }
        return result;
    }

    public static Map<String,Node> reduceCFG(Map<String,String[]> cfg){
        Map<String,Node> nodes = new   HashMap<String,Node>();
        for(String key: cfg.keySet()){
            nodes.put(key,new Node(key));
        }
        for(String key: cfg.keySet()){
           for(String production: cfg.get(key)){
               for(int i=0;i<production.length();i++){
                   if(cfg.containsKey(production.charAt(i)+"")){
                       nodes.get(key).array.add(nodes.get(production.charAt(i)+""));
                   }
               }
           }
        }
        return nodes;
    }

    public static Map<String,String[]> eliminateU(Map<String,Node> nodes,Map<String,String[]> cfg){
        Map<String,String[]> result = new HashMap<String,String[]>();

        HashSet<Node> watched = eliminateUseless(nodes.get("S"));

        for(Node node: watched){
            String val = node.value;
            result.put(val,cfg.get(val));
        }
        return result;
    }

    public static HashSet<Node> eliminateUseless(Node initial){
        Queue<Node> q = new LinkedList<>(); 
        q.add(initial);
        HashSet<Node> h = new HashSet<>();
        h.add(initial);
        while(!q.isEmpty()){
            Node current = q.poll();
            for(Node production: current.array){
                if(!h.contains(production)){
                    q.add(production);
                    h.add(production);
                } 
            }
        }
        return h;
    }
    
}