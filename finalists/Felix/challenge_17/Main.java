package es.felixcoto.tuenti;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Locale;
import java.util.Map;
import java.util.Scanner;

public class Main {
	public static double DOUBLE_PI=Math.PI*2;
	
	
	
	public static void main(String[] args) {
		try {
			Scanner sc=new Scanner(System.in);
			sc.useLocale(Locale.ENGLISH);
			int iNumCases=sc.nextInt();
			int iCasesExecuted=0;
			while (iCasesExecuted<iNumCases){
				Point2D objCenter=new Point2D(sc.nextDouble(), sc.nextDouble());
				Vector2D objTransformToCenterPizza=objCenter.getVectorToPoint(Point2D.ORIGIN);
				double radius=sc.nextDouble();
				int iDifferentIngredientsType=sc.nextInt();
				int iIngredientsTypesProcessed=0;
				Map<String, List<RegularPolygon2D>> objIngredentsList=new HashMap<String, List<RegularPolygon2D>>();
				while (iIngredientsTypesProcessed<iDifferentIngredientsType){
					String sIngredentName=sc.next();
					List<RegularPolygon2D> objCurrentIngredentList;
					if (objIngredentsList.containsKey(sIngredentName)){
						objCurrentIngredentList=objIngredentsList.get(sIngredentName);
					}else{
						objCurrentIngredentList=new ArrayList<RegularPolygon2D>();
						objIngredentsList.put(sIngredentName, objCurrentIngredentList);
					}
					int iSidesOfPolygon=sc.nextInt();
					int iQuantityOfCurrentIngredentType=sc.nextInt();
					int iIngredentsProccesed=0;
					while (iIngredentsProccesed<iQuantityOfCurrentIngredentType){
						// translate all points to make center of pizza the origin of coordinates
						Point2D centerOfPolygon=new Point2D(sc.nextDouble(), sc.nextDouble());
						centerOfPolygon=centerOfPolygon.translate(objTransformToCenterPizza);
						Point2D firstVertex=new Point2D(sc.nextDouble(), sc.nextDouble());
						firstVertex=firstVertex.translate(objTransformToCenterPizza);
						objCurrentIngredentList.add(new RegularPolygon2D(centerOfPolygon, firstVertex, iSidesOfPolygon));
						iIngredentsProccesed++;
					}
					iIngredientsTypesProcessed++;
				}
				boolean bResult=isSolomonicCutPossible( radius, objIngredentsList);
				System.out.println(String.format("Case #%d: %s", iCasesExecuted+1,Boolean.toString(bResult).toUpperCase()));
				iCasesExecuted++;
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	
	private static boolean isSolomonicCutPossible(double objRadius, Map<String, List<RegularPolygon2D>> objIngredentsList) throws Exception {
		boolean bEvenIngredents=true;
		Iterator<List<RegularPolygon2D>> itIngredentsList=objIngredentsList.values().iterator();
		
		// test if there are even number of all types of ingredients
		while (itIngredentsList.hasNext()&& bEvenIngredents){
			List<RegularPolygon2D> objCurrentIngredentList=itIngredentsList.next();
			bEvenIngredents=(objCurrentIngredentList.size()%2)==0;
			
		}
		
		boolean bResult;
		
		if (!bEvenIngredents){
			bResult=false;
		}else{
			
			// find all possible cuts without cut any ingredent 
			itIngredentsList=objIngredentsList.values().iterator();
			List<AnglePortion> objCurrentPossibleCuts=new ArrayList<AnglePortion>();
			objCurrentPossibleCuts.add(new AnglePortion(0, Math.PI));
			
			
			
			//debug lists
			List<List<AnglePortion>> objListOfAnglesToSubstract=new ArrayList<List<AnglePortion>>();
			List<Double> objListOfRelativeAngle=new ArrayList<Double>();
			List<Vector2D[]> objListOfVectors=new ArrayList<Vector2D[]>();
			List<Vector2D> objListOfHighVectors=new ArrayList<Vector2D>();
			List<Vector2D> objListOfLowVectors=new ArrayList<Vector2D>();

			
			// iterate for every ingredient polygon
			while (itIngredentsList.hasNext()&&!objCurrentPossibleCuts.isEmpty()){
				List<RegularPolygon2D> ingredientPositions=itIngredentsList.next();
				Iterator<RegularPolygon2D> itPolygon=ingredientPositions.iterator();
				while (itPolygon.hasNext()&&!objCurrentPossibleCuts.isEmpty()){
					RegularPolygon2D objCurrentPolygon2d=itPolygon.next();
					Point2D[] ingredientVertex=objCurrentPolygon2d.generatePolygonVertex();
					
					
					// convert points to vectors
					Vector2D[] centerToVertex=new Vector2D[ingredientVertex.length];
					for (int i=0;i<centerToVertex.length;i++){
						centerToVertex[i]=Point2D.ORIGIN.getVectorToPoint(ingredientVertex[i]);
					}
					
					
					
					objListOfVectors.add(centerToVertex);
					
					// check limits of angle affected by this polygon
					Vector2D objLowVector=null;
					Vector2D objHighVector=null;
					boolean bCenterInsidePolygonDetected=false;
					for (int i=0;i<centerToVertex.length&&!bCenterInsidePolygonDetected;i++){
						boolean bIsLow=false;
						boolean bIsHigh=false;
						Vector2D objCurrentVector=centerToVertex[i];
						if (objLowVector==null){
							objLowVector=objCurrentVector;
						}else{
							double dRelative=objLowVector.getRelativeAngle(objCurrentVector);
							if (dRelative<0){
								objLowVector=objCurrentVector;
								bIsLow=true;
							}
						}
						
						if (objHighVector==null){
							objHighVector=objCurrentVector;
						}else{
							double dRelative=objHighVector.getRelativeAngle(objCurrentVector);
							if (dRelative>0){
								objHighVector=objCurrentVector;
								bIsHigh=true;
							}
						}
						bCenterInsidePolygonDetected=bIsLow&&bIsHigh;
					}
					
					// check if center is inside polygon
					double dRelativeLowToHigh=objLowVector.getRelativeAngle(objHighVector);
					
					objListOfHighVectors.add(objHighVector);
					objListOfLowVectors.add(objLowVector);
					objListOfRelativeAngle.add(dRelativeLowToHigh);
					
					
					if (bCenterInsidePolygonDetected|| dRelativeLowToHigh<0){
						// center is inside of a polygon, the cut is impossible
						objCurrentPossibleCuts.clear();
					}else{
						// Determine the limits of the polygon and make what angles have to subtract to current cut possibilities 
						List<AnglePortion> anglesToSubstract=new ArrayList<AnglePortion>();
						if (objLowVector.getRelativeAngleTo0()>=0 && objHighVector.getRelativeAngleTo0()>=0){
							anglesToSubstract.add(new AnglePortion(objLowVector.getRelativeAngleTo0(), objHighVector.getRelativeAngleTo0()));
						}else if (objLowVector.getRelativeAngleTo0()<=0 && objHighVector.getRelativeAngleTo0()<=0){
							anglesToSubstract.add(new AnglePortion(objLowVector.getRelativeAngleTo0()+Math.PI, objHighVector.getRelativeAngleTo0()+Math.PI));
						}else{
							if (objHighVector.getRelativeAngleTo0()<0){
								anglesToSubstract.add(new AnglePortion(0, objHighVector.getRelativeAngleTo0()+Math.PI));
								anglesToSubstract.add(new AnglePortion(objLowVector.getRelativeAngleTo0(), Math.PI));
							}
							
							if (objLowVector.getRelativeAngleTo0()<0){
								anglesToSubstract.add(new AnglePortion(0, objHighVector.getRelativeAngleTo0()));
								anglesToSubstract.add(new AnglePortion(objLowVector.getRelativeAngleTo0()+Math.PI, Math.PI));
							}
						}
						if (anglesToSubstract.isEmpty()){
							throw new Exception("angles to substract empty");
						}else{
							
							// Subtract angle
							objListOfAnglesToSubstract.add(anglesToSubstract);
							for(AnglePortion objCurrentAngleToSubstract:anglesToSubstract){
								List<AnglePortion> objNewPossiblePortions=new ArrayList<AnglePortion>();
								for(AnglePortion objCurrentPossibleCut:objCurrentPossibleCuts){
									objNewPossiblePortions.addAll(objCurrentPossibleCut.substract(objCurrentAngleToSubstract));
								}
								objCurrentPossibleCuts=objNewPossiblePortions;
							}
						}
					}
					
				}

			}
			
			if (objCurrentPossibleCuts.isEmpty()){
				bResult=false;
			}else{
				boolean bPosibleCutEven=false;
				// if is possible to make cuts without cut any ingredient, check if any of the possible cuts make possible to divide to half all ingredients
				// to check this, make rotations to simulate the cut is horizontal. If y component is positive ingredient is in upper side, else is in lower side
				Iterator<AnglePortion> itPosibleCuts=objCurrentPossibleCuts.iterator();
				while (!bPosibleCutEven&&itPosibleCuts.hasNext()){
					AnglePortion objCurrentAngle=itPosibleCuts.next();
					
					bPosibleCutEven=true;
					itIngredentsList=objIngredentsList.values().iterator();
					while (bPosibleCutEven&&itIngredentsList.hasNext()){
						List<RegularPolygon2D> ingredientPositions=itIngredentsList.next();
						Iterator<RegularPolygon2D> itPolygon=ingredientPositions.iterator();
						int iDifferenceBetweenHalfs=0;
						while (itPolygon.hasNext()){
							RegularPolygon2D objCurrentPolygon=itPolygon.next();
							Point2D center=objCurrentPolygon.getCenter();
							Point2D centerRotated=center.rotateFromOrigin(-objCurrentAngle.getAngleLow());
							if (centerRotated.getY()>0){
								// Ingredient is in upper side
								iDifferenceBetweenHalfs++;
							}else{
								// Ingredient is in lower side
								iDifferenceBetweenHalfs--;
							}
						}
						bPosibleCutEven=iDifferenceBetweenHalfs==0;
					}
					
				}
				bResult=bPosibleCutEven;
				
				
				
				
				
			}
			
			
		}
		
		
		return bResult;
	}


	
	
	
	
	
	
	
	
}

class Point2D{
	public static final Point2D ORIGIN=new Point2D(0, 0);
	
	
	private double x;
	private double y;
	
	
	public Point2D(double x, double y) {
		this.x = x;
		this.y = y;
	}
	public double getX() {
		return x;
	}
	public double getY() {
		return y;
	}
	
	public Point2D translate(Vector2D objVector){
		double newX=x+objVector.getX();
		double newY=y+objVector.getY();
		return new Point2D(newX,newY);
	}
	
	public Point2D rotateFromOrigin(double dRotateAngle){
		double sinAngle=Math.sin(dRotateAngle);
		double cosAngle=Math.cos(dRotateAngle);
		
		double newX=x*cosAngle-y*sinAngle;
		double newY=y*cosAngle+x*sinAngle;
		
		return new Point2D(newX, newY);
	}
	
	public Vector2D getVectorToPoint(Point2D objOtherPoint){
		return new Vector2D(objOtherPoint.getX()-x,objOtherPoint.getY()-y);
	}
	@Override
	public String toString() {
		return String.format("Point2D [x=%s, y=%s]", x, y);
	}

	
}

class Vector2D{
	
	
	private double x;
	private double y;

	private Double relativeAngleTo0=null;
	
	public Vector2D(double x, double y) {
		this.x = x;
		this.y = y;
	}


	public double getX() {
		return x;
	}


	public double getY() {
		return y;
	}
	
	public Vector2D invertComponents(){
		return new Vector2D(-x, -y);
	}

	public double getRelativeAngle(Vector2D objOtherVector2d){
		double dResult=objOtherVector2d.getRelativeAngleTo0() -this.getRelativeAngleTo0();
		if (dResult>Math.PI){
			dResult=dResult-Main.DOUBLE_PI;
		}else if (dResult<-Math.PI){
			dResult=dResult+Main.DOUBLE_PI;
		}
		return dResult;
	}
	
	public double getRelativeAngleTo0(){
		if (relativeAngleTo0==null){
			relativeAngleTo0=Math.atan2(y,x);
		}
		return relativeAngleTo0;
	}


	@Override
	public String toString() {
		return String.format("Vector2D [x=%s, y=%s, relativeAngleTo0=%s]", x, y, relativeAngleTo0);
	}
	
	
}


class RegularPolygon2D{
	private Point2D center;
	private Point2D firstVertex;
	private int iSides;
	private Point2D[] polygonVertex=null;
	
	/**
	 * @param objCenter
	 * @param objFirstVertex
	 * @param iSides
	 */
	public RegularPolygon2D(Point2D objCenter, Point2D objFirstVertex, int iSides) {
		center = objCenter;
		firstVertex = objFirstVertex;
		this.iSides = iSides;
	}
	
	
	public Point2D[] generatePolygonVertex(){
		if (this.polygonVertex==null){
			polygonVertex=new Point2D[iSides];
			
			//Translate vertex to center
			polygonVertex[0]=firstVertex.translate(center.getVectorToPoint(Point2D.ORIGIN));
			
			// Make rotations to find other points
			
			double centerAngle=Main.DOUBLE_PI/iSides;
			double sinCenterAngle=Math.sin(centerAngle);
			double cosCenterAngle=Math.cos(centerAngle);
			for (int i=1;i<iSides;i++){
				Point2D lastPoint=polygonVertex[i-1];
				double newX=lastPoint.getX()*cosCenterAngle-lastPoint.getY()*sinCenterAngle;
				double newY=lastPoint.getY()*cosCenterAngle+lastPoint.getX()*sinCenterAngle;

				polygonVertex[i]=new Point2D(newX, newY);
			}
			
			// translate to position
			Vector2D translationVector=Point2D.ORIGIN.getVectorToPoint(center);
			for (int i=0;i<polygonVertex.length;i++){
				polygonVertex[i]=polygonVertex[i].translate(translationVector);
			}
		}
		return polygonVertex;
	}


	@Override
	public String toString() {
		return String.format("RegularPolygon2D [center=%s, firstVertex=%s, iSides=%s, polygonVertex=%s]", center, firstVertex, iSides,
				Arrays.toString(polygonVertex));
	}


	public Point2D getCenter() {
		return center;
	}


	public Point2D getFirstVertex() {
		return firstVertex;
	}


	public int getSides() {
		return iSides;
	}

	
	
	
	
}


class AnglePortion{
	private double angleLow;
	private double angleHigh;
	
	public AnglePortion(double angleLow, double angleHigh) {
		this.angleLow = angleLow;
		this.angleHigh = angleHigh;
		if (angleHigh<angleLow){
			throw new IllegalArgumentException("high is lower than low");
		}
	}

	public double getAngleLow() {
		return angleLow;
	}

	public double getAngleHigh() {
		return angleHigh;
	}
	
	public List<AnglePortion> substract(AnglePortion otherPortion){
		List<AnglePortion> result=new ArrayList<AnglePortion>();
		if (otherPortion.getAngleLow()<=angleLow && otherPortion.getAngleHigh()>=angleHigh){
			// other portion subtract all angle
		}else{
			if (otherPortion.getAngleLow()>=angleHigh || otherPortion.getAngleHigh()<=angleLow){
				// other portion don't intersect with portion
				result.add(this);
			}else{
				if (otherPortion.getAngleLow()>angleLow && otherPortion.getAngleHigh()<angleHigh){
					// split the angle in 2
					result.add(new AnglePortion(angleLow, otherPortion.getAngleLow()));
					result.add(new AnglePortion(otherPortion.getAngleHigh(), angleHigh));
				}else{
					// The result is quit some part of angle
					if (otherPortion.getAngleLow()>angleLow){
						result.add(new AnglePortion(angleLow,otherPortion.getAngleLow()));
					}else{
						result.add(new AnglePortion(otherPortion.getAngleHigh(),angleHigh));
					}
					
				}
			}
		}
		return result;
	}

	@Override
	public String toString() {
		return String.format("AnglePortion [angleLow=%s, angleHigh=%s]", angleLow, angleHigh);
	}
	
	
}