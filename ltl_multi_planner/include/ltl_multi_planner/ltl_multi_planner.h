#ifndef LTL_MULTI_PLANNER__LTL_MULTI_PLANNER_H_
#define LTL_MULTI_PLANNER__LTL_MULTI_PLANNER_H_
#include <multi_robot_move/multi_planner_base.h>
#include <multi_robot_move/ordered_pose_stamped.h>
#include <ltl_multi_planner/primitive.h>
#include <ltl_multi_planner/readinputs.h>
#include <string>
#include <ros/ros.h>

typedef std::vector<position> pos_vec_t;

namespace ltl_multi_planner
{
	class LtlMultiPlanner : public multi_planner_base::MultiPlanner
	{
	public:

		void initialize();
		bool makePlan(std::vector<ordered_pose_stamped::OrderedPoseStamped>& start_poses,
		          std::vector<ordered_pose_stamped::OrderedPoseStamped>& goal_poses,
				  std::map<ordered_pose_stamped::OrderedPoseStamped, std::vector<ordered_pose_stamped::OrderedPoseStamped> >& assignments,
				  std::map<ordered_pose_stamped::OrderedPoseStamped, std::map<ordered_pose_stamped::OrderedPoseStamped, std::vector<ordered_pose_stamped::OrderedPoseStamped> > >& plans);

		LtlMultiPlanner();
	private:
		double multiPathCostTolerance;
		bool final_smt_cost_optimization;
		string primitives_filename;
		string z3TimeoutInSeconds;
		prim_vec_t primitives;
		dimension_t dimension;
		pos_vec_t obstacles;
		std::vector<position_with_cost> alwaysEventuallyFreeObstacles;
		bool initialized_;
		string static_files_folder, system_config_files_folder;
		double map_scale, map_width, map_resolution;
		bool findPosition (pos_vec_t posvec, position pos);
		void generateZ3File(prim_vec_t primitives, pos_vec_t obstacles, vector<position_with_cost> alwaysEventuallyFreeConstraints, workspace_t workspace);
		position metersToImplanUnits(pos_2d pos);
		position metersToImplanUnits2(int x, int y);
		pos_2d implanUnitsToMeters(position pos);
		void generateTrajectories(prim_vec_t primitives, dimension_t dimension, pos_vec_t obstacles, pos_vec_t initpos, pos_vec_t finalpos, int max_length);
		void createWorkspace(dimension_t dimension, pos_vec_t initposition);
		pos_vec_t convertPosesIntoScaledPositions_( std::vector<ordered_pose_stamped::OrderedPoseStamped>& poses, std::map<position, ordered_pose_stamped::OrderedPoseStamped>& conversion_map);
		std::vector<ordered_pose_stamped::OrderedPoseStamped> convertScaledPositionsIntoPoses(pos_vec_t & positions);
		int findTheGreatestManhattanDistance(pos_vec_t initpos, pos_vec_t finalpos);
		std::map<string, std::vector<ordered_pose_stamped::OrderedPoseStamped> > readAndConvertPropositions();

	};
};

#endif
