#ifndef CPFA_LOOP_FUNCTIONS_H
#define CPFA_LOOP_FUNCTIONS_H

#include <argos3/core/simulator/loop_functions.h>
#include <argos3/plugins/robots/foot-bot/simulator/footbot_entity.h>
#include <argos3/core/simulator/entity/floor_entity.h>
#include <source/CPFA/CPFA_controller.h>
#include <random>
#include <argos3/plugins/simulator/entities/cylinder_entity.h>

using namespace argos;

static const size_t GENOME_SIZE = 7; // There are 7 parameters to evolve

class CPFA_loop_functions : public argos::CLoopFunctions
{

	friend class CPFA_controller;
	friend class CPFA_qt_user_functions;

	public:

		CPFA_loop_functions();
	   
		void Init(argos::TConfigurationNode &t_tree);
		void Reset();
		void PreStep();
		void PostStep();
		bool IsExperimentFinished();
		void PostExperiment();
		argos::CColor GetFloorColor(const argos::CVector2 &c_pos_on_floor);

		// GA Functions
		
		/* Configures the robot controller from the genome */
		void ConfigureFromGenome(Real* pf_genome);
		/* Calculates the performance of the robot in a trial */
		Real Score();
	
		/**
		 * Returns the current trial.
		 */
		UInt32 GetTrial() const;
	
		/**
		 * Sets the current trial.
		 * @param un_trial The trial number.
		 */
		void SetTrial(UInt32 un_trial);
	
		/* public helper functions */
		void UpdatePheromoneList();
		void SetFoodDistribution();

		argos::Real getSimTimeInSeconds();

		std::vector<argos::CColor>   TargetRayColorList;

		unsigned int getNumberOfRobots();
		double getProbabilityOfSwitchingToSearching();
		double getProbabilityOfReturningToNest();
		double getUninformedSearchVariation();
		double getRateOfInformedSearchDecay();
		double getRateOfSiteFidelity();
		double getRateOfLayingPheromone();
		double getRateOfPheromoneDecay();

	protected:

		void setScore(double s);

		argos::CRandom::CRNG* RNG;
                size_t NumDistributedFood; //qilu 11/10/2016
		
		size_t MaxSimTime;
		size_t ResourceDensityDelay;
		size_t RandomSeed;
		size_t SimCounter;
		size_t MaxSimCounter;
		size_t VariableFoodPlacement;
		size_t OutputData;
		size_t DrawDensityRate;
		size_t DrawIDs;
		size_t DrawTrails;
		size_t DrawTargetRays;
		size_t FoodDistribution;
		size_t FoodItemCount;
		size_t NumberOfClusters;
		size_t ClusterWidthX;
		size_t ClusterLengthY;
                size_t PowerRank;
                size_t ArenaWidth;
        size_t SimTime; //qilu 09/13/2016
        Real curr_time_in_minutes; //qilu 09/13/2016
        Real last_time_in_minutes; //qilu 09/13/2016
        int Nest_travel_time_in_ticks;
        size_t Num_robots;
        
        Real CollisionTime;//qilu 09/26
        size_t lastNumCollectedFood; //qilu 08/19
        size_t currNumCollectedFood; //qilu 08/19

		/* CPFA variables */
		argos::Real ProbabilityOfSwitchingToSearching;
		argos::Real ProbabilityOfReturningToNest;
		argos::CRadians UninformedSearchVariation;
		argos::Real RateOfInformedSearchDecay;
		argos::Real RateOfSiteFidelity;
		argos::Real RateOfLayingPheromone;
		argos::Real RateOfPheromoneDecay;

		/* physical robot & world variables */
		argos::Real FoodRadius;
		argos::Real FoodRadiusSquared;
		argos::Real NestRadius;
		argos::Real NestRadiusSquared;
		argos::Real NestElevation;
		argos::Real SearchRadiusSquared;

        argos::Real NestPosition_0; //qilu 09/06/2016
        argos::Real NestPosition_1;
        argos::Real NestPosition_2;
        argos::Real NestPosition_3;
  
        vector<CCylinderEntity> Cylinders; //qilu 10/18/2016
        
		/* list variables for food & pheromones */
		std::vector<argos::CVector2> FoodList;
		std::vector<argos::CColor>   FoodColoringList;
		vector<size_t>               FoodClusterIDs;
		vector<Real>                 FoodDistances;
		
		std::vector<argos::CRay3>    TargetRayList;
		argos::CRange<argos::Real>   ForageRangeX;
		argos::CRange<argos::Real>   ForageRangeY;
  
    
  
  std::vector<Nest> Nests; //qilu 09/06
  vector<size_t>	ForageList; //qilu 09/13
	private:

		/* private helper functions */
  void GaussianFoodDistribution();
		void RandomFoodDistribution();
		void ClusterFoodDistribution();
		void PowerLawFoodDistribution();
  bool IsOutOfArena(argos::CVector2 p);
		bool IsOutOfArena(argos::CVector2 p, argos::Real radius);
  bool IsOutOfBounds(argos::CVector2 p, size_t length, size_t width);
  bool IsOutOfBounds(argos::CVector2 p, argos::Real radius); //qilu 07/26/2016 for nest
		bool IsCollidingWithNest(argos::CVector2 p);
		bool IsCollidingWithFood(argos::CVector2 p);
  bool IsCollidingWithNest(argos::CVector2 p, argos::Real radius); //qilu 07/26/2016 for nest
  bool IsCollidingWithFood(argos::CVector2 p, argos::Real radius);//qilu 07/26/2016 for nest
  void CreateNest(argos::CVector2 position); //qilu 07/26/2016
  void ReallocateNests();
  vector<CVector2> ComputeNewCenters();
  vector<CVector2> Clustering(vector<CVector2>);
  void Centroidal_Voronoi_tessellation(vector<CVector2> centers);
  vector<CColor> ClusterColorList;
  
		double score;
		int PrintFinalScore;
};

#endif /* CPFA_LOOP_FUNCTIONS_H */
