package es.felixcoto.tuenti.bee;

import java.util.HashMap;
import java.util.Map;

public enum BeeCommands {
	INCREMENT_POINTER("Bee. Bee?") {
		@Override
		public void execute(BeeMachine objBeeMachine) {
			objBeeMachine.incrementPointer();
		}
	},
	DECREMENT_POINTER("Bee? Bee.") {
		@Override
		public void execute(BeeMachine objBeeMachine) {
			objBeeMachine.decrementPointer();
			
		}
	},
	INCREMENT_VALUE("Bee. Bee.") {
		@Override
		public void execute(BeeMachine objBeeMachine) {
			objBeeMachine.incrementValue();
			
		}
	},
	DECREMENT_VALUE("Bee! Bee!") {
		@Override
		public void execute(BeeMachine objBeeMachine) {
			objBeeMachine.decrementValue();
		}
	},
	BRANCH_IF_0("Bee! Bee?") {
		@Override
		public void execute(BeeMachine objBeeMachine) {
			objBeeMachine.branch(this);
			
		}
	},
	BRANCH_IF_NOT_0("Bee? Bee!") {
		@Override
		public void execute(BeeMachine objBeeMachine) {
			objBeeMachine.branch(this);
			
		}
	},
	PRINT("Bee! Bee.") {
		@Override
		public void execute(BeeMachine objBeeMachine) {
			objBeeMachine.print();
		}
	};
	private final String sCode;
	
	private BeeCommands(String sCode) {
		this.sCode=sCode;
	}
	
	
	
	public abstract void execute(BeeMachine objBeeMachine);
	
	private static Map<String, BeeCommands> lookupTable=new HashMap<String, BeeCommands>();
	static{
		for(BeeCommands objCurrentBeeCommand:BeeCommands.values()){
			BeeCommands.lookupTable.put(objCurrentBeeCommand.getCode(),objCurrentBeeCommand);
		}
	}
	
	public static BeeCommands lookup(String sCode){
		return lookupTable.get(sCode);
	}
	
	public String getCode() {
		return sCode;
	}
	
}
