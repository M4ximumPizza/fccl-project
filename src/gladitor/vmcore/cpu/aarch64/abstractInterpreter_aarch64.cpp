int AbstractInterpreter::BasicType_as_index(BasicType type) {
  // Maps BasicType to an index
  switch (type) {
    case T_BOOLEAN: return 0;
    case T_CHAR   : return 1;
    case T_BYTE   : return 2;
    case T_SHORT  : return 3;
    case T_INT    : return 4;
    case T_LONG   : return 5;
    case T_VOID   : return 6;
    case T_FLOAT  : return 7;
    case T_DOUBLE : return 8;
    case T_OBJECT :
    case T_ARRAY  : return 9;
    default       : ShouldNotReachHere(); // Unexpected type
  }
  assert(false, "Index out of bounds"); // Assert if the index is out of bounds
  return -1; // Default return
}

int AbstractInterpreter::size_top_interpreter_activation(Method* method) {
  // Calculate activation size for the top interpreter frame
  const int entry_size = frame::interpreter_frame_monitor_size();
  const int overhead_size = -(frame::interpreter_frame_initial_sp_offset) + entry_size;
  const int stub_code = frame::entry_frame_after_call_words;
  const int method_stack = (method->max_locals() + method->max_stack()) * Interpreter::stackElementWords;
  return (overhead_size + method_stack + stub_code);
}

int AbstractInterpreter::size_activation(int max_stack,
                                         int temps,
                                         int extra_args,
                                         int monitors,
                                         int callee_params,
                                         int callee_locals,
                                         bool is_top_frame) {
  // Calculate activation size
  int overhead = frame::sender_sp_offset - frame::interpreter_frame_initial_sp_offset;
  int size = overhead + (callee_locals - callee_params) * Interpreter::stackElementWords +
             monitors * frame::interpreter_frame_monitor_size() +
             (is_top_frame ? max_stack : temps + extra_args);
  size = align_up(size, 2); // Aligning size on AArch64
  return size;
}

void AbstractInterpreter::layout_activation(Method* method,
                                            int temp_count,
                                            int popframe_extra_args,
                                            int monitor_count,
                                            int caller_actual_parameters,
                                            int callee_param_count,
                                            int callee_locals,
                                            frame* caller,
                                            frame* interpreter_frame,
                                            bool is_top_frame,
                                            bool is_bottom_frame) {
  // Layout the activation frame
  const int max_locals = method->max_locals() * Interpreter::stackElementWords;
  const int params = method->size_of_parameters() * Interpreter::stackElementWords;
  const int extra_locals = max_locals - params;

  assert(caller->sp() == interpreter_frame->sender_sp(), "Frame not properly walkable");

  interpreter_frame->interpreter_frame_set_method(method);

  intptr_t* locals = caller->is_interpreted_frame()
    ? caller->interpreter_frame_last_sp() + caller_actual_parameters - 1
    : interpreter_frame->sender_sp() + max_locals - 1;

  assert(!caller->is_interpreted_frame() || locals < caller->fp() + frame::interpreter_frame_initial_sp_offset, "Bad placement");

  interpreter_frame->interpreter_frame_set_locals(locals);
  BasicObjectLock* montop = interpreter_frame->interpreter_frame_monitor_begin();
  BasicObjectLock* monbot = montop - monitor_count;
  interpreter_frame->interpreter_frame_set_monitor_end(monbot);

  intptr_t* esp = (intptr_t*)monbot -
    temp_count * Interpreter::stackElementWords -
    popframe_extra_args;
  interpreter_frame->interpreter_frame_set_last_sp(esp);

  int max_stack = method->constMethod()->max_stack() + MAX2(3, Method::extra_stack_entries());
  intptr_t* extended_sp = (intptr_t*)monbot -
    (max_stack * Interpreter::stackElementWords) -
    popframe_extra_args;
  extended_sp = align_down(extended_sp, StackAlignmentInBytes);
  interpreter_frame->interpreter_frame_set_extended_sp(extended_sp);

  if (extra_locals != 0 && interpreter_frame->sender_sp() == interpreter_frame->interpreter_frame_sender_sp()) {
    interpreter_frame->set_interpreter_frame_sender_sp(caller->sp() + extra_locals);
  }

  *interpreter_frame->interpreter_frame_cache_addr() = method->constants()->cache();
  *interpreter_frame->interpreter_frame_mirror_addr() = method->method_holder()->java_mirror();
}