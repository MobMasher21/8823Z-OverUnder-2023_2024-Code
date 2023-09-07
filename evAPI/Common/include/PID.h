/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       PID.h                                                     */
/*    Author:       Jackson Area Robotics                                     */
/*    Created:      ???                                                       */
/*    Description:  PID class.                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifndef PID_H
#define PID_H

namespace evAPI
{
  class PID
  {
    private:
      //double error = 0;
      double KP = 0;
      double KI = 0;
      double KD = 0;
      double starti = 0;
      double settle_error = 0;
      double settle_time = 0;
      double timeout = 0;
      long accumulated_error = 0;
      double previous_error = 0;
      double output = 0;
      double time_spent_settled = 0;
      double time_spent_running = 0;

    public:

      /**
       * @brief Creates a PID object.
       * @param error Starting error
       * @param kp KP Value
       * @param ki KI Value
       * @param kd KD Value
       * @param starti
       * @param settle_error
       * @param settle_time
       * @param timeout
      */
      PID(double error, double kp, double ki, double kd, double starti, double settle_error, double settle_time, double timeout);

      PID(double error, double kp, double ki, double kd, double starti);

      double compute(double error);

      bool is_settled();

      /**
       * @brief Sets constants used for the PID function.
       * @param kp The KP factor.
       * @param ki The KI factor.
       * @param kd The KD factor.
      */
      void setConstants(double kp, double ki, double kd);
  };
}

#endif // PID_H