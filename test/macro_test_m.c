# 1 "macro_test.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "macro_test.c"







void porter_transport(void) {
  num_f( p_state, 2 );
  switch( p_state ) {
  case P_WAIT_FOR_LOADING:
    if( p_is_entry ) {
      p_is_entry = false;
      timer_start( 10000 );
    }
    if( carrier_cargo_is_loaded() ) {
      p_state = P_TRANSPORTING;
      p_is_entry = true;
    }
    if( timer_is_timedout() ) {
      p_state = P_TIMED_OUT;
      p_is_entry = true;
    }
    if( p_is_entry ) {
      timer_stop();
    }
    break;
  case P_TIMED_OUT:
    horn_confirmation();
    p_state = P_WAIT_FOR_LOADING;
    p_is_entry = true;
    if(p_is_entry){p_is_entry=false;
      horn_confirmation();
    }{
    (if((true)){p_state=(P_WAIT_FOR_LOADING);p_is_entry=true;})
    }if(p_is_entry){
    }
    break;
  }
}
