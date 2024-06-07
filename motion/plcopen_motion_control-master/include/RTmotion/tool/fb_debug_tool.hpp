/*
 * Copyright (c) 2020 Intel Corporation
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @file fb_debug_tool.hpp
 *
 * Maintainer: Yu Yan <yu.yan@intel.com>
 *
 */

#include <vector>
#include <string>
#include <sstream>
#include <chrono>
#include <algorithm>
#include <pybind11/embed.h>
#include <pybind11/stl.h>

#ifdef PLOT
//#include <RTmotion/plot/matplotlibcpp.h>
//namespace plt = matplotlibcpp
namespace py = pybind11;

#endif

std::vector<std::string> split_string_by_period(std::string name)
{
  std::vector<std::string> tokens;

  std::stringstream ss(name);

  std::string intermediate;

  // Tokenizing w.r.t. period '.'
  while (std::getline(ss, intermediate, '.'))
  {
    tokens.push_back(intermediate);
  }

  return tokens;
}

struct SearchResult
{
  bool found;
  size_t index;
};

struct FB
{
  std::string name_;
  std::vector<std::string> digital_names_;
  std::vector<std::vector<double>> digital_states_;

  FB(std::string name)
  {
    name_ = name;
  }

  SearchResult findDigitalItem(std::string item)
  {
    SearchResult res;
    auto it = std::find(digital_names_.begin(), digital_names_.end(), item);

    res.found = (it != digital_names_.end());
    res.index = std::distance(digital_names_.begin(), it);

    return res;
  }
};

class FBDigitalProfile
{
public:
  FBDigitalProfile() = default;
  virtual ~FBDigitalProfile() = default;

  SearchResult findFB(std::string name)
  {
    SearchResult res;
    auto it =
        std::find_if(fbs_.begin(), fbs_.end(), [name](const FB& item) -> bool {
          return item.name_ == name;
        });

    res.found = (it != fbs_.end());
    res.index = std::distance(fbs_.begin(), it);

    return res;
  }

  void addFB(std::string name)
  {
    if (!findFB(name).found)
      fbs_.push_back(FB(name));
  }

  bool checkItemName(std::string item, std::string& fb_name,
                     std::string& var_name)
  {
    std::vector<std::string> res = split_string_by_period(item);

    if (res.size() != 2)
    {
      printf("Invalid item name: '%s', item name should be "
             "'<function_block_name>.<digital_variable_name>'.\n",
             item.c_str());
      return false;
    }

    fb_name = res[0];
    var_name = res[1];
    return true;
  }

  bool addItemName(std::string item)
  {
    std::string fb_name, var_name;
    if (!checkItemName(item, fb_name, var_name))
      return false;

    SearchResult fb_search = findFB(fb_name);
    if (!fb_search.found)  // FB not exists
    {
      printf("Function block '%s' not existing.\n", fb_name.c_str());
      return false;
    }

    if (fbs_[fb_search.index].findDigitalItem(var_name).found)  // Digital item
                                                                // already
                                                                // exists
    {
      printf("Item '%s' already exists.\n", var_name.c_str());
      return false;
    }

    fbs_[fb_search.index].digital_names_.push_back(var_name);
    fbs_[fb_search.index].digital_states_.push_back(std::vector<double>{});
    printf("Add item '%s' to the debugger of function block '%s'\n",
           var_name.c_str(), fb_name.c_str());
    return true;
  }

  bool addState(std::string item, int state)
  {
    std::string fb_name, var_name;
    if (!checkItemName(item, fb_name, var_name))
      return false;

    SearchResult fb_search = findFB(fb_name);
    if (!fb_search.found)  // FB not exists
    {
      printf("Function block '%s' not existing.", fb_name.c_str());
      return false;
    }

    SearchResult var_search = fbs_[fb_search.index].findDigitalItem(var_name);
    if (!var_search.found)  // Digital item not exists
    {
      printf("Item '%s' not exists. Please add first.", var_name.c_str());
      return false;
    }

    fbs_[fb_search.index].digital_states_[var_search.index].push_back(state);
    return true;
  }

  void addTime(double time)
  {
    time_stamps_.push_back(time);
  }

  void reset()
  {
    fbs_.clear();
    time_stamps_.clear();
  }

  size_t getItemCount()
  {
    size_t n = 0;
    for (auto fb : fbs_)
      n += fb.digital_names_.size();
    return n;
  }

  void plot(std::string file_name = "digital_profile.png",
            std::string prefix = "FB", int width = 1280, int height = 1024)
  {
#ifdef PLOT
    // Set the size of output image to 1280x720 pixels
    //plt::figure_size(1280, 1024);
    py::module_ plt = py::module_::import("matplotlib.pyplot");
    size_t n = getItemCount();
    size_t plot_order = 0;
    //printf("itemcount: %d \n",n);

    for (size_t j = 0; j < fbs_.size(); ++j)
    {
      for (size_t i = 0; i < fbs_[j].digital_names_.size(); ++i)
      {
        plot_order++;

        if (plot_order == 1)
          plt.attr("title")("Function Block Waveform");

        plt.attr("subplot")(n, 1, plot_order);
        plt.attr("plot")(time_stamps_, fbs_[j].digital_states_[i],"r-");
        plt.attr("ylabel")(std::to_string(j + 1) + "." + fbs_[j].digital_names_[i]);
        plt.attr("grid")(true);
        plt.attr("ylim")(-0.2, 2.2);

      }
      plt.attr("xlabel")("time");
    }    
    plt.attr("savefig")(file_name); 

#endif
  }

private:
  std::vector<FB> fbs_;
  std::vector<double> time_stamps_;
};

class AxisProfile
{
public:
  AxisProfile() = default;
  virtual ~AxisProfile() = default;

  void addState(double pos, double vel, double time)
  {
    pos_.push_back(pos);
    vel_.push_back(vel);
    time_stamps_.push_back(time);
  }

  void reset()
  {
    pos_.clear();
    vel_.clear();
    time_stamps_.clear();
  }

  void plot(std::string file_name = "axis_profile.png")
  {
#ifdef PLOT    

    try {
       // py::scoped_interpreter guard{}; // Initialize the Python interpreter
        py::module_ plt = py::module_::import("matplotlib.pyplot");
        
        //plt.attr("subplots")(2, 2);
        plt.attr("title")("Scurve Figure Waveform");
        plt.attr("subplot")(2, 1, 1);
        plt.attr("plot")(time_stamps_, pos_,"r-");
        plt.attr("ylabel")("Position");
        plt.attr("grid")(true);

        plt.attr("subplot")(2, 1, 2);
        plt.attr("plot")(time_stamps_, vel_,"b-");
        plt.attr("ylabel")("velocity");
        plt.attr("grid")(true);

        plt.attr("xlabel")("Time");
        plt.attr("savefig")(file_name); 

        //plt.attr("save")(file_name);

    } catch (const py::error_already_set& e) {
        std::cerr << "Python error: " << e.what() << std::endl;
    }
/*
    // Set the size of output image to 1280x360 pixels
    plt::figure_size(1280, 360);
    // Plot line from given t and pos
    plt::subplot(2, 1, 1);
    plt::title("Axis Profile");
    plt::named_plot("Position", time_stamps_, pos_, "tab:blue");
    plt::ylabel("Position");
    // Plot line from given t and vel
    plt::subplot(2, 1, 2);
    plt::named_plot("Velocity", time_stamps_, vel_, "tab:orange");
    plt::ylabel("Velocity");
    plt::xlabel("time");
    // Save the image (file format is determined by the extension)
    plt::save(file_name);*/
#endif
  }

private:
  std::vector<double> pos_;
  std::vector<double> vel_;
  std::vector<double> time_stamps_;
};