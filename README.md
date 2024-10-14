# `kon_F6L_KisBeadand` package
ROS 2 C++ package.  [![Static Badge](https://img.shields.io/badge/ROS_2-Humble-34aec5)](https://docs.ros.org/en/humble/)

A teknőc a rendelkezésre álló területet körbejárja és egy őnvezető fűnyírót szimulálna.
## Packages and build

It is assumed that the workspace is `~/ros2_ws/`.

### Clone the packages
``` r
cd ~/ros2_ws/src
```
``` r
git clone https://github.com/konya7/kon_F6L_KisBeadand-.git
```

### Build ROS 2 packages
``` r
cd ~/ros2_ws
```
``` r
colcon build --packages-select mower_sim --symlink-install
```

<details>
<summary> Don't forget to source before ROS commands.</summary>

``` bash
source ~/ros2_ws/install/setup.bash
```
</details>

``` r
ros2 run turtlesim turtlesim_node

```

``` r
ros2 run mower_sim mower_draw

```

## Graph

``` mermaid
flowchart TD

U([/mower_draw]):::red -->  CMD[ /turtle1/cmd_vel<br/>geometry_msgs/Twist]:::light --> S([/sim]):::red

classDef light fill:#34aec5,stroke:#152742,stroke-width:2px,color:#152742  
classDef dark fill:#152742,stroke:#34aec5,stroke-width:2px,color:#34aec5
classDef white fill:#ffffff,stroke:#152742,stroke-width:2px,color:#152742
classDef red fill:#ef4638,stroke:#152742,stroke-width:2px,color:#fff
```
