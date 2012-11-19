#ifndef CUIMG_MDFL_DETECTOR_H_
# define CUIMG_MDFL_DETECTOR_H_

# include <cuimg/improved_builtin.h>
# include <cuimg/cpu/host_image2d.h>

namespace cuimg
{

  class mdfl_1s_detector
  {
  public:
    inline mdfl_1s_detector(const obox2d& d);

    inline void update(const host_image2d<gl8u>& input);

    template <typename F, typename PS>
    inline void new_particles(const F& feature, PS& pset);

    inline mdfl_1s_detector& set_contrast_threshold(float f);
    inline mdfl_1s_detector& set_dev_threshold(float f);

    inline const host_image2d<gl01f>& saliency() { return saliency_; }

  private:
    float contrast_th_;
    float dev_th_;
    host_image2d<gl01f> saliency_;
  };

}

# include <cuimg/tracking2/mdfl_detector.hpp>

#endif