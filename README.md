{% if cookiecutter.library_prefix -%}
    {% set prefix = cookiecutter.library_prefix | capitalize + "_" -%}
{% else -%}
    {% set prefix = '' -%}
{% endif -%}
{% set repo_name = prefix + cookiecutter.library_name -%}
{% set full_repo_name = cookiecutter.github_user + "/" + repo_name -%}


{{repo_name}} [![Build Status](https://travis-ci.com/adafruit/{{cookiecutter.repo_name}}.svg?branch=master)](https://travis-ci.com/adafruit/{{cookiecutter.repo_name}})
================

{% if cookiecutter.pid -%}
<a href="https://www.adafruit.com/products/{{cookiecutter.pid}}"><img src="assets/board.jpg?raw=true" width="500px"></a>
{% else -%}
<a href="https://www.adafruit.com/products"><img src="assets/board.jpg?raw=true" width="500px"></a>
{% endif -%}

This is the {{cookiecutter.lib_human_name}} {{cookiecutter.sensor_description}}

{% if cookiecutter.pid -%}
Tested and works great with the Adafruit LPS35HW Breakout Board 
* <a href="https://www.adafruit.com/products/{{cookiecutter.pid}}"><img src="assets/board.jpg?raw=true" width="500px"></a>
{% endif -%}

This chip uses I2C to communicate, 2 pins are required to interface

Adafruit invests time and resources providing this open source code, please support Adafruit and open-source hardware by purchasing products from Adafruit!
################################################

{%- if cookiecutter.requires_busio in ["y", "yes"] %}
* `Adafruit_BusIO <https://github.com/adafruit/Adafruit_BusIO>`_
{%- endif %}
{%- if cookiecutter.requires_sensor in ["y", "yes"] %}
* `Adafruit_Sensor <https://github.com/adafruit/Adafruit_Sensor>`_
{%- endif %}

Contributing
============

Contributions are welcome! Please read our `Code of Conduct
<https://github.com/{{ full_repo_name }}/blob/master/CODE_OF_CONDUCT.md>`_
before contributing to help this project stay welcoming.

# Doxygen example and basics/link to guide
https://learn.adafruit.com/the-well-automated-arduino-library/doxygen
https://learn.adafruit.com/the-well-automated-arduino-library/doxygen-tips
##########################
Written by {{ cookiecutter.attrubution}}.  
BSD license, check license.txt for more information
All text above must be included in any redistribution

To install, use the Arduino Library Manager and search for "{{cookiecutter.human_name}}" and install the library.
