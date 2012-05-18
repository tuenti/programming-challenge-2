package es.felixcoto.tuenti;

import java.util.Deque;
import java.util.HashMap;
import java.util.Map;

public enum M00reCommands {
	SUM("@") {
		@Override
		public void execute(Deque<Long> objStack) {
			long lFirst=objStack.pop();
			long lSecond=objStack.pop();
			long lResult=lFirst+lSecond;
			objStack.push(lResult);
		}
	},
	SUBSTRACT("$") {
		@Override
		public void execute(Deque<Long> objStack) {
			long lSubtrahend=objStack.pop();
			long lMinuend=objStack.pop();
			long lResult=lMinuend-lSubtrahend;
			objStack.push(lResult);
		}
	},
	MULTIPLICATION("#") {
		@Override
		public void execute(Deque<Long> objStack) {
			long lFirst=objStack.pop();
			long lSecond=objStack.pop();
			long lResult=lFirst*lSecond;
			objStack.push(lResult);
		}
	},
	DIVISION("&") {
		@Override
		public void execute(Deque<Long> objStack) {
			long lDivisor=objStack.pop();
			long lDividend=objStack.pop();
			long lResult=lDividend/lDivisor;
			objStack.push(lResult);
		}
	},
	PRINT(".") {
		@Override
		public void execute(Deque<Long> objStack) {
			long lResult=objStack.pop();
			System.out.println(lResult);
		}
	},
	MOD("conquer") {
		@Override
		public void execute(Deque<Long> objStack) {
			long lDivisor=objStack.pop();
			long lDividend=objStack.pop();
			long lResult=lDividend%lDivisor;
			
			objStack.push(lResult);
		}
	},
	DUPLICATE("breadandfish") {
		@Override
		public void execute(Deque<Long> objStack) {
			long lResult=objStack.peek();
			objStack.push(lResult);
		}
	},
	MAX("fire") {
		@Override
		public void execute(Deque<Long> objStack) {
			long lFirst=objStack.pop();
			long lSecond=objStack.pop();
			long lResult=Math.max(lFirst, lSecond);
			objStack.push(lResult);
		}
	},
	NEGATIVE("mirror") {
		@Override
		public void execute(Deque<Long> objStack) {
			long lResult=objStack.pop();
			lResult=-lResult;
			objStack.push(lResult);
		}
	},
	REVERSE_ORDER("dance") {
		@Override
		public void execute(Deque<Long> objStack) {
			long lFirst=objStack.pop();
			long lSecond=objStack.pop();
			objStack.push(lFirst);
			objStack.push(lSecond);
		}
	};
	private final String opcode;
	
	private M00reCommands(String opcode){
		this.opcode=opcode;
	}
	
	public abstract void execute(Deque<Long> objStack);
	
	
	private static Map<String, M00reCommands> lookup=new HashMap<String, M00reCommands>();
	static{
		for (M00reCommands objCurrentOperator : M00reCommands.values()) {
			lookup.put(objCurrentOperator.getOpcode(), objCurrentOperator);
		}
	}
	
	public static M00reCommands lookupOperator(String sOpcode){
		return lookup.get(sOpcode);
	}

	public String getOpcode() {
		return opcode;
	}
	
	
	
}
