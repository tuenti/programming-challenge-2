package es.felixcoto.tuenti.bee;

import java.io.ByteArrayOutputStream;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;


public class BeeMachine {
	List<Long> objArray;
	int iPointer;
	ByteArrayOutputStream bo;
	boolean bBranching;
	BeeCommands objCommandOpenBranch=null;
	BeeCommands objCommandCloseBranch=null;
	int iInitBranchLeftToClose=0;
	int iDirection=1;
	List<BeeCommands> objCode;

	
	public BeeMachine(InputStream in){
		objCode=new ArrayList<BeeCommands>();
		compile(in);
	}
	
	
	private void compile(InputStream in) {
		Scanner sc=new Scanner(in);
		while (sc.hasNext()){
			StringBuilder sb=new StringBuilder();
			sb.append(sc.next());
			sb.append(" ");
			sb.append(sc.next());
			BeeCommands objBeeCommand=BeeCommands.lookup(sb.toString());
			if (objBeeCommand==null){
				throw new IllegalArgumentException("Code Error");
			}
			objCode.add(objBeeCommand);
		}
		
	}


	protected void incrementPointer(){
		if (!bBranching){
			iPointer++;
			if (objArray.size()==iPointer){
				objArray.add(0l);
			}
		}
	}
	
	protected void decrementPointer(){
		if (!bBranching) {
			iPointer--;
			if (iPointer < 0) {
				throw new ArrayIndexOutOfBoundsException(iPointer);
			}
		}
	}
	
	protected void incrementValue(){
		if (!bBranching) {
			objArray.set(iPointer, objArray.get(iPointer) + 1);
		}
	}
	
	protected void decrementValue(){
		if (!bBranching) {
			objArray.set(iPointer, objArray.get(iPointer) - 1);
		}
	}

	protected void branch(BeeCommands objCurrentCommand){	
		if (bBranching){
			if (objCurrentCommand.equals(objCommandOpenBranch)){
				iInitBranchLeftToClose++;
			}else{
				if (objCurrentCommand.equals(objCommandCloseBranch)){
					iInitBranchLeftToClose--;
					if (iInitBranchLeftToClose==0){
						bBranching=false;
					}
					iDirection=1;
				}
			}
		}else{
			if (BeeCommands.BRANCH_IF_0.equals(objCurrentCommand)&& objArray.get(iPointer)==0){
				bBranching=true;
				iInitBranchLeftToClose++;
				objCommandOpenBranch=BeeCommands.BRANCH_IF_0;
				objCommandCloseBranch=BeeCommands.BRANCH_IF_NOT_0;
			}else{
				if (BeeCommands.BRANCH_IF_NOT_0.equals(objCurrentCommand) && objArray.get(iPointer)!=0){
					bBranching=true;
					iInitBranchLeftToClose++;
					objCommandOpenBranch=BeeCommands.BRANCH_IF_NOT_0 ;
					objCommandCloseBranch=BeeCommands.BRANCH_IF_0;
					iDirection=-1;
				}
			}
		}
	}
	
	protected void print(){
		if (!bBranching){
			bo.write(objArray.get(iPointer).intValue());
		}
	}
	
	public String process(){
		iPointer=0;
		objArray=new ArrayList<Long>();
		objArray.add(0l);
		bBranching=false;
		bo=new ByteArrayOutputStream();
		iDirection=1;
		for (int i=0;i<objCode.size();i+=iDirection){
			BeeCommands objCommand=objCode.get(i);
			objCommand.execute(this);
		}

		
		
		return new String(bo.toByteArray());
	}


	
	

}
