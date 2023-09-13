#include "state.h"
#include "axisData.h"
namespace stepperState {
	/**
	 * @brief This state sets the axis to idle on entry.
	 * @details This state sets the axis to idle on entry.
	 * It does nothing on tick and exit.
	 * @see State
	 * @see AxisData
	*/
	class IdleState : public State
	{
	private:
		/// @brief The axis data reference
		AxisData& axisData;
	public:
		/// @brief Constructs a new IdleState object
		/// @param axisData The axis data reference
		IdleState(AxisData& axisData);
		~IdleState();

		void tick() override;
		void reset() override;
		void exit() override;
	};

} // namespace stepperState