---
target: /config/vm.args
---
{% set config_map = env.get('CONFIG_MAP', 'couchdb') %}
{% set config = kube.get('configmap', config_map).data -%}

# Turn off the sasl error logger
-sasl sasl_error_logger false

# Use the following erlang hostname
{% if config.get('erlang.hostname') == 'long' %}
-name couchdb
{% else %}
-sname couchdb
{% endif %}

# Use kernel poll functionality if supported by emulator
+K true

# Maximum number of processes
+P {{ env.get('ERLANG_PROCESSES', 2048) }}

# Start a pool of asynchronous IO threads
+A {{ env.get('ERLANG_THREADS', 32) }}

# Turn off the kernel error_logger
-kernel error_logger silent

# Set erlang distribution to use 11500-11999 ports instead of random
# predictibility has value here
-kernel inet_dist_listen_min 11500 inet_dist_listen_max 11999

# Comment this line out if you want the Erlang shell
+Bd -noinput
