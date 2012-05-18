package es.felixcoto.tuenti;

import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;

public class CloningMachine {
	
	Map<Character,String> completeTransformations;
	
	
	public CloningMachine(List<String> arrayConfig){
		Map<Character,String> transformations=new HashMap<Character, String>();
		
		for (String sLineConfig : arrayConfig) {
			Map<Character,String> newTransformationsResult=new HashMap<Character, String>();
			Map<Character,String> newTransformations=new HashMap<Character, String>();
			String[] arrayTransformation=sLineConfig.split(",");
			for (String sTransformation : arrayTransformation) {
				char cOriginal=sTransformation.charAt(0);
				String sClone=sTransformation.substring(3);
				newTransformations.put(cOriginal, sClone);
				if (!transformations.containsKey(cOriginal)){
					newTransformationsResult.put(cOriginal, sClone);
				}
			}
			for (Entry<Character, String> entryTrans : transformations.entrySet()) {
				String sNewTransFormation=processTransformation(entryTrans.getValue(), newTransformations);
				newTransformationsResult.put(entryTrans.getKey(), sNewTransFormation);
			}
			transformations=newTransformationsResult;
		}
		completeTransformations=transformations;
		
		
	}
	
	
	private String processTransformation(String origin,Map<Character, String> transformations){
		StringBuilder sb=new StringBuilder();
		for(int i=0;i<origin.length();i++){
			char cCurrentPerson=origin.charAt(i);
			if (transformations.containsKey(cCurrentPerson)){
				sb.append(transformations.get(cCurrentPerson));
			}else{
				sb.append(cCurrentPerson);
			}
		}
		return sb.toString();
	}
	
	
	
	public String processPerson(char cPerson){
		if (completeTransformations.containsKey(cPerson)){
			return completeTransformations.get(cPerson);
		}else{
			return Character.toString(cPerson);
		}
	}

}
