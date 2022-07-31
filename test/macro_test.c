
#define ENTRY if(p_is_entry){p_is_entry=false;
#define DO }{
#define EVCHK(f,s) (if((f)){p_state=(s);p_is_entry=true;})
#define EXIT }if(p_is_entry){
#define END }

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
    ENTRY
      horn_confirmation();
    DO
    EVTCHK(true,P_WAIT_FOR_LOADING)
    EXIT
    END
    break;
  }
}
