do_package_checks(warnings_are_errors = (getRversion() >= "3.2"))

if (Sys.getenv("BUILD_PKGDOWN") != "") {
  get_stage("before_deploy") %>%
    add_step(step_setup_ssh()) # why is this skipping?

  get_stage("deploy") %>%
    add_step(step_build_pkgdown()) %>% 
    add_step(step_push_deploy())
}
