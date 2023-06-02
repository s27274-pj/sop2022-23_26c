project('zajecia4', 'c',
        default_options : ['c_std=gnu99', 'warning_level=3', 'werror=true'])

c = run_command('../globber.sh', check: true)
srcs = c.stdout().strip().split('\0')
foreach src : srcs
  if src != ''
    parts = src.split('/')
    name = parts[parts.length() - 1].substring(0, -2)
    executable(name, src)
  endif
endforeach

executable('zadaniedom', ['zadaniedom/main.c', 'zadaniedom/handler.c'])

run_target('fmt',
           command : '../formatter.sh')
