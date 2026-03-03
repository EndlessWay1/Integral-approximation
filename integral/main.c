// Made by Nickson Kiyoshi
// Computing the integral base on the rieman integral

#include "../base.h"


#define MAX_OPERATOR 2

typedef enum {
    X_OP_NULL = 0,
    X_OP_CREATE,
    
    X_OP_CONSTANT,
    
    _X_OP_UNARY_START,
    X_OP_EXP,
    X_OP_LN,
    X_OP_ABS,
    // trig
    X_OP_SIN,
    X_OP_COS,
    X_OP_TAN,
    // hyperbolic trig
    X_OP_TANH,
    X_OP_COSH,
    X_OP_SINH,
    // atrig
    X_OP_ASIN,
    X_OP_ACOS,
    X_OP_ATAN,
    X_OP_ACSC,
    X_OP_ACOT,
    X_OP_ASEC,
    // hiper argtrig
    X_OP_ASINH,
    X_OP_ACOSH,
    X_OP_ATANH,
    X_OP_ACSCH,
    X_OP_ACOTH,
    X_OP_ASECH,

    _X_OP_BINARY_START,
    // basic ops
    X_OP_ADD,
    X_OP_SUB,
    X_OP_MUL,
    X_OP_DIV,
    
    // pow function
    X_OP_POW


} X_ops;

#define X_NUM_INPUT(op) ((op) < _X_OP_UNARY_START) ? 0: (((op) < _X_OP_BINARY_START)? 1 : 2)

typedef enum {
    X_FLAG_NONE     = 0,
    X_FLAG_INPUT    = (1 << 0),
    X_FLAG_OUTPUT   = (1 << 1)
} X_flags;


typedef struct X_operator{
    u32 index;
    u32 flags;
    X_ops op;
    matrix* data;

    struct X_operator* inputs[MAX_OPERATOR];

} X_operator;

typedef struct {
    X_operator** ops;
    u32 size;
} X_function;

typedef struct {
    u32 num_size;
    u32 n;
    f128 limit_above;
    f128 limit_below;

    X_operator* input;
    X_operator* output;
    
    X_function function;
} X_integral;

X_operator* op_create(
    mem_arena* arena, X_integral* model, u32 flag
);

X_operator* _x_binary_impl(
    mem_arena* arena, X_integral* model,
    X_operator* a, X_operator* b, X_ops op, u32 flag);

X_operator* _x_unary_impl(
    mem_arena* arena, X_integral* model,
    X_operator* a, X_ops op, u32 flag);

    // basic ops
X_operator* x_op_add(
    mem_arena* arena, X_integral* model,
    X_operator* a, X_operator* b, u32 flag);

X_operator* x_op_sub(
    mem_arena* arena, X_integral* model,
    X_operator* a, X_operator* b, u32 flag);

X_operator* x_op_mul(
    mem_arena* arena, X_integral* model,
    X_operator* a, X_operator* b, u32 flag);

X_operator* x_op_div(
    mem_arena* arena, X_integral* model,
    X_operator* a, X_operator* b, u32 flag);

X_operator* x_op_exp(
    mem_arena* arena, X_integral* model,
    X_operator* x, u32 flag);

X_operator* x_op_ln(
    mem_arena* arena, X_integral* model,
    X_operator* x, u32 flag);

X_operator* x_op_abs(
    mem_arena* arena, X_integral* model,
    X_operator* a, u32 flag);

X_operator* x_op_sin(
    mem_arena* arena, X_integral* model,
    X_operator* a, u32 flag);

X_operator* x_op_cos(
    mem_arena* arena, X_integral* model,
    X_operator* a, u32 flag);

X_operator* x_op_tan(
    mem_arena* arena, X_integral* model,
    X_operator* a, u32 flag);

X_operator* x_op_tanh(
    mem_arena* arena, X_integral* model,
    X_operator* a, u32 flag);

X_operator* x_op_cosh(
    mem_arena* arena, X_integral* model,
    X_operator* a, u32 flag);

X_operator* x_op_sinh(
    mem_arena* arena, X_integral* model,
    X_operator* a, u32 flag);

X_operator* x_op_pow(
    mem_arena* arena, X_integral* model,
    X_operator* a, X_operator* b, u32 flag);

X_operator* x_op_asin(
    mem_arena* arena, X_integral* model,
    X_operator* a, u32 flag);

X_operator* x_op_acos(
    mem_arena* arena, X_integral* model,
    X_operator* a, u32 flag);

X_operator* x_op_atan(
    mem_arena* arena, X_integral* model,
    X_operator* a, u32 flag);

X_operator* x_op_acsc(
    mem_arena* arena, X_integral* model,
    X_operator* a, u32 flag);

X_operator* x_op_acot(
    mem_arena* arena, X_integral* model,
    X_operator* a, u32 flag);

X_operator* x_op_asec(
    mem_arena* arena, X_integral* model,
    X_operator* a, u32 flag);

X_operator* x_op_asinh(
    mem_arena* arena, X_integral* model,
    X_operator* a, u32 flag);

X_operator* x_op_acosh(
    mem_arena* arena, X_integral* model,
    X_operator* a, u32 flag);

X_operator* x_op_atanh(
    mem_arena* arena, X_integral* model,
    X_operator* a, u32 flag);

X_operator* x_op_acsch(
    mem_arena* arena, X_integral* model,
    X_operator* a, u32 flag);

X_operator* x_op_acoth(
    mem_arena* arena, X_integral* model,
    X_operator* a, u32 flag);

X_operator* x_op_asech(
    mem_arena* arena, X_integral* model,
    X_operator* a, u32 flag);

X_operator* x_op_constant(
    mem_arena* arena, X_integral* model, const f128 c, u32 flag);

// binary ops
b32 op_add(matrix* dst, const matrix* a, const matrix* b);
b32 op_sub(matrix* dst, const matrix* a, const matrix* b);
b32 op_div(matrix* dst, const matrix* a, const matrix* b);
b32 op_mul(matrix* dst, const matrix* a, const matrix* b);
b32 op_pow(matrix* dst, const matrix* a, const matrix* b);

// unary ops
b32 op_exp(matrix* dst, const matrix* a);
b32 op_ln(matrix* dst, const matrix* a);
b32 op_abs(matrix* dst, const matrix* a);
b32 op_sin(matrix* dst, const matrix* a);
b32 op_cos(matrix* dst, const matrix* a);
b32 op_tan(matrix* dst, const matrix* a);

b32 op_tanh(matrix* dst, const matrix* a);
b32 op_cosh(matrix* dst, const matrix* a);
b32 op_sinh(matrix* dst, const matrix* a);
b32 op_asin(matrix* dst, const matrix* a);
b32 op_acos(matrix* dst, const matrix* a);
b32 op_atan(matrix* dst, const matrix* a);

b32 op_acsc(matrix* dst, const matrix* a);
b32 op_acot(matrix* dst, const matrix* a);
b32 op_asec(matrix* dst, const matrix* a);

b32 op_asinh(matrix* dst, const matrix* a);
b32 op_acosh(matrix* dst, const matrix* a);
b32 op_atanh(matrix* dst, const matrix* a);

b32 op_acsch(matrix* dst, const matrix* a);
b32 op_acoth(matrix* dst, const matrix* a);
b32 op_asech(matrix* dst, const matrix* a);


X_function integral_function(mem_arena* arena, X_integral* integral, X_operator* out_ops);
f128 integral_compute(X_integral* integral, f128 upper, f128 lower);
X_integral* integral_create(mem_arena* arena, u32 n_subdiv);
void integral_compile(mem_arena* arena, X_integral* integral);

void create_x_si_integral(mem_arena* arena, X_integral* model);

int main (void){
    mem_arena* perm_arena = arena_create(GiB(1), MiB(1));
    X_integral* integral = integral_create(perm_arena, (1 << 20));
    create_x_si_integral(perm_arena, integral);

    printf("Volume Result: %Lf\n", integral_compute(integral, 2*M_PI, 1E-9));

    arena_destroy(perm_arena);
    return 0;
}


void create_x_si_integral(mem_arena* arena, X_integral* model){
    X_operator* input = op_create(arena, model, X_FLAG_INPUT);
    X_operator* sin = x_op_sin(arena, model, input, 0);
    x_op_div(arena, model, sin, input, X_FLAG_OUTPUT);
    // x_op_exp(arena, model, multi, X_FLAG_OUTPUT);
    
    integral_compile(arena, model);
}


X_operator* op_create(
    mem_arena* arena, X_integral* model, u32 flag
){
    X_operator* out = PUSH_STRUCT(arena, X_operator);
    
    out->index = model->num_size;
    out->data = mat_create(arena, model->n, 1);
    model->num_size++;
    out->flags = flag;
    out->op = X_OP_CREATE;

    if (flag & X_FLAG_INPUT) {model->input = out;}
    if (flag & X_FLAG_OUTPUT) {model->output = out;}
    
    return out;
}



X_operator* _x_binary_impl(
    mem_arena* arena, X_integral* model,
    X_operator* a, X_operator* b, X_ops op, u32 flag
){
    X_operator* operator = op_create(arena, model, flag);
    operator->inputs[0] = a;
    operator->inputs[1] = b;

    operator->op = op;
    return operator;
}

X_operator* _x_unary_impl(
    mem_arena* arena, X_integral* model,
    X_operator* a, X_ops op, u32 flag
){
    X_operator* operator = op_create(arena, model, flag);
    operator->inputs[0] = a;

    operator->op = op;
    return operator;
}


X_operator* x_op_add(
    mem_arena* arena, X_integral* model,
    X_operator* a, X_operator* b, u32 flag){
    if ((a->data->row != b->data->row) ||
    (a->data->col != b->data->col)){
        return NULL;
    }
    
    return _x_binary_impl(
        arena, model, a, 
        b, X_OP_ADD, flag
    );
}

X_operator* x_op_sub(
    mem_arena* arena, X_integral* model,
    X_operator* a, X_operator* b, u32 flag){
    if ((a->data->row != b->data->row) ||
    (a->data->col != b->data->col)){
        return NULL;
    }
    
    return _x_binary_impl(
        arena, model, a, 
        b, X_OP_SUB, flag
    );
}

X_operator* x_op_mul(
    mem_arena* arena, X_integral* model,
    X_operator* a, X_operator* b, u32 flag){
    if ((a->data->row != b->data->row) ||
    (a->data->col != b->data->col)){
        return NULL;
    }
    
    return _x_binary_impl(
        arena, model, a, 
        b, X_OP_MUL, flag
    );
}

X_operator* x_op_div(
    mem_arena* arena, X_integral* model,
    X_operator* a, X_operator* b, u32 flag){
    if ((a->data->row != b->data->row) ||
    (a->data->col != b->data->col)){
        return NULL;
    }
    
    return _x_binary_impl(
        arena, model, a, 
        b, X_OP_DIV, flag
    );
}

X_operator* x_op_exp(
    mem_arena* arena, X_integral* model,
    X_operator* x, u32 flag){

    return _x_unary_impl(
        arena, model, x, 
        X_OP_EXP, flag
    );
}

X_operator* x_op_ln(
    mem_arena* arena, X_integral* model,
    X_operator* x, u32 flag){
    
    return _x_unary_impl(
        arena, model, x, 
        X_OP_LN, flag
    );
}

X_operator* x_op_abs(
    mem_arena* arena, X_integral* model,
    X_operator* a, u32 flag){
    
    return _x_unary_impl(
        arena, model, a, 
        X_OP_ABS,flag
    );
}

X_operator* x_op_sin(
    mem_arena* arena, X_integral* model,
    X_operator* a, u32 flag){
    
    return _x_unary_impl(
        arena, model, a, 
        X_OP_SIN, flag
    );
}

X_operator* x_op_cos(
    mem_arena* arena, X_integral* model,
    X_operator* a, u32 flag){
    
    return _x_unary_impl(
        arena, model, a, 
        X_OP_COS, flag
    );
}

X_operator* x_op_tan(
    mem_arena* arena, X_integral* model,
    X_operator* a, u32 flag){
    
    return _x_unary_impl(
        arena, model, a, 
        X_OP_TAN, flag
    );
}

X_operator* x_op_tanh(
    mem_arena* arena, X_integral* model,
    X_operator* a, u32 flag){
    
    return _x_unary_impl(
        arena, model, a, 
        X_OP_TANH,flag
    );
}

X_operator* x_op_cosh(
    mem_arena* arena, X_integral* model,
    X_operator* a, u32 flag){
    
    return _x_unary_impl(
        arena, model, a, 
        X_OP_COSH,flag
    );
}

X_operator* x_op_sinh(
    mem_arena* arena, X_integral* model,
    X_operator* a, u32 flag){
    
    return _x_unary_impl(
        arena, model, a, 
        X_OP_SINH, flag
    );
}

X_operator* x_op_pow(
    mem_arena* arena, X_integral* model,
    X_operator* a, X_operator* b, u32 flag){
    if ((a->data->row != b->data->row) ||
    (a->data->col != b->data->col)){
        return NULL;
    }
    
    return _x_binary_impl(
        arena, model, a, b,
        X_OP_POW, flag
    );
}

X_operator* x_op_asin(
    mem_arena* arena, X_integral* model,
    X_operator* a, u32 flag){
    
    return _x_unary_impl(
        arena, model, a, 
        X_OP_ASIN,flag
    );
}

X_operator* x_op_acos(
    mem_arena* arena, X_integral* model,
    X_operator* a, u32 flag){
    
    return _x_unary_impl(
        arena, model, a, 
        X_OP_ACOS,flag
    );
}

X_operator* x_op_atan(
    mem_arena* arena, X_integral* model,
    X_operator* a, u32 flag){
    
    return _x_unary_impl(
        arena, model, a, 
        X_OP_ATAN,flag
    );
}

X_operator* x_op_acsc(
    mem_arena* arena, X_integral* model,
    X_operator* a, u32 flag){
    
    return _x_unary_impl(
        arena, model, a, 
        X_OP_ACSC,flag
    );
}

X_operator* x_op_acot(
    mem_arena* arena, X_integral* model,
    X_operator* a, u32 flag){
    
    return _x_unary_impl(
        arena, model, a, 
        X_OP_ACOT,flag
    );
}

X_operator* x_op_asec(
    mem_arena* arena, X_integral* model,
    X_operator* a, u32 flag){
    
    return _x_unary_impl(
        arena, model, a, 
        X_OP_ASEC,flag
    );
}

X_operator* x_op_asinh(
    mem_arena* arena, X_integral* model,
    X_operator* a, u32 flag){
    
    return _x_unary_impl(
        arena, model, a, 
        X_OP_ASINH,flag
    );
}

X_operator* x_op_acosh(
    mem_arena* arena, X_integral* model,
    X_operator* a, u32 flag){
    
    return _x_unary_impl(
        arena, model, a, 
        X_OP_ACOSH,flag
    );
}

X_operator* x_op_atanh(
    mem_arena* arena, X_integral* model,
    X_operator* a, u32 flag){
    
    return _x_unary_impl(
        arena, model, a, 
        X_OP_ATANH,flag
    );
}

X_operator* x_op_acsch(
    mem_arena* arena, X_integral* model,
    X_operator* a, u32 flag){
    
    return _x_unary_impl(
        arena, model, a, 
        X_OP_ACSCH,flag
    );
}

X_operator* x_op_acoth(
    mem_arena* arena, X_integral* model,
    X_operator* a, u32 flag){
    
    return _x_unary_impl(
        arena, model, a, 
        X_OP_ACOTH,flag
    );
}

X_operator* x_op_asech(
    mem_arena* arena, X_integral* model,
    X_operator* a, u32 flag){
    
    return _x_unary_impl(
        arena, model, a, 
        X_OP_ASECH,flag
    );
}


X_operator* x_op_constant(
    mem_arena* arena, X_integral* model, const f128 c, u32 flag){
    
    X_operator* out = op_create(arena, model, flag);
    out->op = X_OP_CONSTANT;
    mat_fill(out->data, c);
    return out;
}


// binary ops
b32 op_add(matrix* dst, const matrix* a, const matrix* b){
    return mat_add(dst, a, b);
}

b32 op_sub(matrix* dst, const matrix* a, const matrix* b){
    return mat_sub(dst, a, b);
}

b32 op_div(matrix* dst, const matrix* a, const matrix* b){
    if(dst->col != a->col || dst->col != b->col) return false;
    if(dst->row != a->row || dst->row != b->row) return false;

    u64 size = (u64) a->col*a->row;
    for (u64 i = 0; i < size; i++){
        dst->data[i] = (fabsl(b->data[i]) > EPS) ? (a->data[i] / b->data[i]): INFINITY;
    }
    return true;
}

b32 op_mul(matrix* dst, const matrix* a, const matrix* b){
    if(dst->col != a->col || dst->col != b->col) return false;
    if(dst->row != a->row || dst->row != b->row) return false;
    
    u64 size = (u64) a->col*a->row;
    for (u64 i = 0; i < size; i++){
        dst->data[i] = (a->data[i] * b->data[i]);
    }
    return true;
}

b32 op_pow(matrix* dst, const matrix* a, const matrix* b){
    if(dst->col != a->col || dst->col != b->col) return false;
    if(dst->row != a->row || dst->row != b->row) return false;
    
    u64 size = (u64) a->col*a->row;
    for (u64 i = 0; i < size; i++){
        dst->data[i] = powl(a->data[i], b->data[i]);
    }
    return true;
}


b32 op_exp(matrix* dst, const matrix* a){
    if(dst->col != a->col || dst->row != a->row) return false;
    
    u64 size = (u64) a->col*a->row;
    for (u64 i = 0; i < size; i++){
        dst->data[i] = expl(a->data[i]);
    }
    return true;
}

b32 op_ln(matrix* dst, const matrix* a){
    if(dst->col != a->col || dst->row != a->row) return false;
    
    u64 size = (u64) a->col*a->row;
    for (u64 i = 0; i < size; i++){
        dst->data[i] = logl(a->data[i]);
    }
    return true;
}

b32 op_abs(matrix* dst, const matrix* a){
    if(dst->col != a->col || dst->row != a->row) return false;
    
    u64 size = (u64) a->col*a->row;
    for (u64 i = 0; i < size; i++){
        dst->data[i] = fabsl(a->data[i]);
    }
    return true;
}

b32 op_sin(matrix* dst, const matrix* a){
    if(dst->col != a->col || dst->row != a->row) return false;
    
    u64 size = (u64) a->col*a->row;
    for (u64 i = 0; i < size; i++){
        dst->data[i] = sinl(a->data[i]);
    }
    return true;
}

b32 op_cos(matrix* dst, const matrix* a){
    if(dst->col != a->col || dst->row != a->row) return false;
    
    u64 size = (u64) a->col*a->row;
    for (u64 i = 0; i < size; i++){
        dst->data[i] = cosl(a->data[i]);
    }
    return true;
}

b32 op_tan(matrix* dst, const matrix* a){
    if(dst->col != a->col || dst->row != a->row) return false;
    
    u64 size = (u64) a->col*a->row;
    for (u64 i = 0; i < size; i++){
        dst->data[i] = tanl(a->data[i]);
    }
    return true;
}

b32 op_tanh(matrix* dst, const matrix* a){
    if(dst->col != a->col || dst->row != a->row) return false;
    
    u64 size = (u64) a->col*a->row;
    for (u64 i = 0; i < size; i++){
        dst->data[i] = tanhl(a->data[i]);
    }
    return true;
}

b32 op_cosh(matrix* dst, const matrix* a){
    if(dst->col != a->col || dst->row != a->row) return false;
    
    u64 size = (u64) a->col*a->row;
    for (u64 i = 0; i < size; i++){
        dst->data[i] = coshl(a->data[i]);
    }
    return true;
}
b32 op_sinh(matrix* dst, const matrix* a){
    if(dst->col != a->col || dst->row != a->row) return false;
    
    u64 size = (u64) a->col*a->row;
    for (u64 i = 0; i < size; i++){
        dst->data[i] = sinhl(a->data[i]);
    }
    return true;
}

b32 op_asin(matrix* dst, const matrix* a){
    if(dst->col != a->col || dst->row != a->row) return false;
    
    u64 size = (u64) a->col*a->row;
    for (u64 i = 0; i < size; i++){
        dst->data[i] = asinl(a->data[i]);
    }
    return true;
}

b32 op_acos(matrix* dst, const matrix* a){
    if(dst->col != a->col || dst->row != a->row) return false;
    
    u64 size = (u64) a->col*a->row;
    for (u64 i = 0; i < size; i++){
        dst->data[i] = acoshl(a->data[i]);
    }
    return true;
}

b32 op_atan(matrix* dst, const matrix* a){
    if(dst->col != a->col || dst->row != a->row) return false;
    
    u64 size = (u64) a->col*a->row;
    for (u64 i = 0; i < size; i++){
        dst->data[i] = atanl(a->data[i]);
    }
    return true;
}

b32 op_acsc(matrix* dst, const matrix* a){
    if(dst->col != a->col || dst->row != a->row) return false;
    
    u64 size = (u64) a->col*a->row;
    mem_arena_temp scratch = arena_scratch_get(NULL, 0);
    matrix* m = mat_create(scratch.arena, a->row, a->col);
    mat_fill(m, 1.0f);

    op_div(dst, m, a);

    for (u64 i = 0; i < size; i++){
        dst->data[i] = asinl(a->data[i]);
    }

    arena_scratch_release(scratch);

    return true;
}

b32 op_acot(matrix* dst, const matrix* a){
        if(dst->col != a->col || dst->row != a->row) return false;
    
    u64 size = (u64) a->col*a->row;
    mem_arena_temp scratch = arena_scratch_get(NULL, 0);
    matrix* m = mat_create(scratch.arena, a->row, a->col);
    mat_fill(m, 1.0f);

    op_div(dst, m, a);

    for (u64 i = 0; i < size; i++){
        dst->data[i] = atanl(a->data[i]);
    }

    arena_scratch_release(scratch);

    return true;
}

b32 op_asec(matrix* dst, const matrix* a){
    if(dst->col != a->col || dst->row != a->row) return false;
    
    u64 size = (u64) a->col*a->row;
    mem_arena_temp scratch = arena_scratch_get(NULL, 0);
    matrix* m = mat_create(scratch.arena, a->row, a->col);
    mat_fill(m, 1.0f);

    op_div(dst, m, a);

    for (u64 i = 0; i < size; i++){
        dst->data[i] = acosl(a->data[i]);
    }

    arena_scratch_release(scratch);

    return true;
}

b32 op_asinh(matrix* dst, const matrix* a){
    if(dst->col != a->col || dst->row != a->row) return false;
    
    u64 size = (u64) a->col*a->row;
    for (u64 i = 0; i < size; i++){
        dst->data[i] = asinhl(a->data[i]);
    }
    return true;
}

b32 op_acosh(matrix* dst, const matrix* a){
    if(dst->col != a->col || dst->row != a->row) return false;
    
    u64 size = (u64) a->col*a->row;
    for (u64 i = 0; i < size; i++){
        dst->data[i] = acoshl(a->data[i]);
    }
    return true;

}

b32 op_atanh(matrix* dst, const matrix* a){
    if(dst->col != a->col || dst->row != a->row) return false;
    
    u64 size = (u64) a->col*a->row;
    for (u64 i = 0; i < size; i++){
        dst->data[i] = atanhl(a->data[i]);
    }
    return true;

}

b32 op_acsch(matrix* dst, const matrix* a){
    if(dst->col != a->col || dst->row != a->row) return false;
    
    u64 size = (u64) a->col*a->row;
    mem_arena_temp scratch = arena_scratch_get(NULL, 0);
    matrix* m = mat_create(scratch.arena, a->row, a->col);
    mat_fill(m, 1.0f);

    op_div(dst, m, a);

    for (u64 i = 0; i < size; i++){
        dst->data[i] = asinhl(a->data[i]);
    }

    arena_scratch_release(scratch);

    return true;

}

b32 op_acoth(matrix* dst, const matrix* a){
    if(dst->col != a->col || dst->row != a->row) return false;
    
    u64 size = (u64) a->col*a->row;
    mem_arena_temp scratch = arena_scratch_get(NULL, 0);
    matrix* m = mat_create(scratch.arena, a->row, a->col);
    mat_fill(m, 1.0f);

    op_div(dst, m, a);

    for (u64 i = 0; i < size; i++){
        dst->data[i] = atanhl(a->data[i]);
    }

    arena_scratch_release(scratch);

    return true;

}

b32 op_asech(matrix* dst, const matrix* a){
    if(dst->col != a->col || dst->row != a->row) return false;
    
    u64 size = (u64) a->col*a->row;
    mem_arena_temp scratch = arena_scratch_get(NULL, 0);
    matrix* m = mat_create(scratch.arena, a->row, a->col);
    mat_fill(m, 1.0f);

    op_div(dst, m, a);

    for (u64 i = 0; i < size; i++){
        dst->data[i] = acoshl(a->data[i]);
    }

    arena_scratch_release(scratch);

    return true;

}


X_integral* integral_create(mem_arena* arena, u32 n_subdiv){
    if (n_subdiv == 0) return NULL;
    X_integral* in = PUSH_STRUCT(arena, X_integral);
    in->n = n_subdiv + 1;
    in->num_size = 0;
    return in;
}

X_function integral_function(mem_arena* arena, X_integral* integral, X_operator* out_ops){
    mem_arena_temp scratch = arena_scratch_get(&arena, 1);

    b8* visited = PUSH_ARRAY_NZ(scratch.arena, b8, integral->num_size);

    u32 stack_size = 0;
    u32 out_size = 0;

    X_operator** stack = PUSH_ARRAY(scratch.arena, X_operator*, integral->num_size);
    X_operator** out = PUSH_ARRAY(scratch.arena, X_operator*, integral->num_size);

    stack[stack_size++] = out_ops;
    
    while(stack_size > 0){
        X_operator* cur = stack[--stack_size];

        if (cur->index >= integral->num_size) continue;

        if (visited[cur->index]) {
            if (out_size < integral->num_size){
                out[out_size++] = cur;
            }
            continue;
        }

        visited[cur->index] = true;
        if (stack_size < integral->num_size){
            stack[stack_size++] = cur;
        }

        u32 num_input = X_NUM_INPUT(cur->op);
        for (u32 i = 0 ; i < num_input; i++){
            X_operator* input = cur->inputs[i];

            if (input->index >= integral->num_size || visited[input->index]){
                continue;
            }

            for (u32 j = 0; j < stack_size; j++){
                if (stack[j] == input){
                    for (u32 k = j; k < stack_size - 1; k++){
                        stack[k] = stack[k+1];
                    }
                    stack_size--;
                }
            }
            if (stack_size < integral->num_size){
                stack[stack_size++] = input;
            }
        }

    }

    X_function func = {
        .size = out_size,
        .ops = PUSH_ARRAY_NZ(arena, X_operator*, out_size)
    };

    memcpy(func.ops, out, sizeof(X_operator*)* out_size);
    arena_scratch_release(scratch);
    return func;
}

void integral_prog_compute(X_function* func){
    for (u32 i = 0; i < func->size; i++){
        X_operator* cur = func->ops[i];

        X_operator* a = cur->inputs[0];
        X_operator* b = cur->inputs[1];

        switch (cur->op){

            case X_OP_NULL:
            case X_OP_CREATE: break;

            case X_OP_CONSTANT: break;
            case _X_OP_UNARY_START: break;
            
            case X_OP_EXP: {op_exp(cur->data, a->data);} break;
            case X_OP_LN: {op_ln(cur->data, a->data);}break;
            case X_OP_ABS: {op_abs(cur->data, a->data);} break;
            
            case X_OP_SIN: {op_sin(cur->data, a->data);}break;
            case X_OP_COS: {op_cos(cur->data, a->data);}break;
            case X_OP_TAN: {op_tan(cur->data, a->data);}break;
            
            case X_OP_TANH: {op_tanh(cur->data, a->data);}break;
            case X_OP_COSH: {op_cosh(cur->data, a->data);}break;
            case X_OP_SINH: {op_sinh(cur->data, a->data);}break;

            case X_OP_ASIN: {op_asin(cur->data, a->data);}break;
            case X_OP_ACOS: {op_acos(cur->data, a->data);}break;
            case X_OP_ATAN: {op_atan(cur->data, a->data);}break;
            case X_OP_ACSC: {op_acsc(cur->data, a->data);}break;
            case X_OP_ACOT: {op_acot(cur->data, a->data);}break;
            case X_OP_ASEC: {op_asec(cur->data, a->data);}break;
            
            case X_OP_ASINH: {op_asinh(cur->data, a->data);}break;
            case X_OP_ACOSH: {op_acosh(cur->data, a->data);}break;
            case X_OP_ATANH: {op_atanh(cur->data, a->data);}break;
            case X_OP_ACSCH: {op_acsch(cur->data, a->data);}break;
            case X_OP_ACOTH: {op_acoth(cur->data, a->data);}break;
            case X_OP_ASECH: {op_asech(cur->data, a->data);}break;
            
            case _X_OP_BINARY_START: break;
            
            case X_OP_ADD: {op_add(cur->data, a->data, b->data);}break;
            case X_OP_SUB: {op_sub(cur->data, a->data, b->data);}break;
            case X_OP_MUL: {op_mul(cur->data, a->data, b->data);}break;
            case X_OP_DIV: {op_div(cur->data, a->data, b->data);}break;
            case X_OP_POW: {op_pow(cur->data, a->data, b->data);}break;

        }
        // printf("Operation: %i\n", cur->op);
        // printf("%Lf\n", cur->data->data[0]);
        // print_mat(cur->data);
    }
}

f128 integral_compute(X_integral* integral, f128 upper, f128 lower){
    if (integral->output == NULL || integral->input == NULL) return NAN;
    if (lower > upper) return NAN;

    f128 delta = upper - lower;
    f128 delta_div_n = delta/(integral->n);
    // printf("detlta: %Lf\n", delta_div_n);

    integral->input->data->data[0] = lower;
    for (u32 i = 1 ; i < integral->n; i++){
        integral->input->data->data[i] = integral->input->data->data[i - 1] + delta_div_n;
    }

    // printf("Ori: %Lf, %f\n", integral->input->data->data[integral->n - 1] + delta_div_n, M_PI_2);

    integral_prog_compute(&integral->function);

    // printf("Res: %Lf\n",integral->output->data->data[integral->n - 2]);
    
    mat_scale(integral->output->data, delta_div_n);

    f128 total = mat_sum(integral->output->data);
    return total;
}

void integral_compile(mem_arena* arena, X_integral* integral){
    if (integral->output != NULL){
        integral->function = integral_function(arena, integral, integral->output);
    }
}
