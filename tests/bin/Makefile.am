TESTS = random_boolean_test     \
        random_integer_test     \
        bipartite_graph_test    \
        complete_graph_test     \
        cycle_graph_test        \
        grid_graph_test         \
        uniform_tree_test       \
        game_payoff_test        \
        game_p_i_test           \
        game_p_ij_test 

noinst_PROGRAMS = $(TESTS)

random_boolean_test_CFLAGS = $(DEPS_CFLAGS) 
random_boolean_test_LDADD  = $(DEPS_LIBS)
random_boolean_test_SOURCES = ../random/random_boolean_test.c @top_srcdir@/src/random.c

random_integer_test_CFLAGS = $(DEPS_CFLAGS)
random_integer_test_LDADD  = $(DEPS_LIBS)
random_integer_test_SOURCES = ../random/random_integer_test.c @top_srcdir@/src/random.c

bipartite_graph_test_CFLAGS = $(DEPS_CFLAGS)
bipartite_graph_test_LDADD  = $(DEPS_LIBS)
bipartite_graph_test_SOURCES = ../graph/bipartite_graph_test.c @top_srcdir@/src/graph.c

complete_graph_test_CFLAGS = $(DEPS_CFLAGS)
complete_graph_test_LDADD  = $(DEPS_LIBS)
complete_graph_test_SOURCES = ../graph/complete_graph_test.c @top_srcdir@/src/graph.c

cycle_graph_test_CFLAGS = $(DEPS_CFLAGS)
cycle_graph_test_LDADD  = $(DEPS_LIBS)
cycle_graph_test_SOURCES = ../graph/cycle_graph_test.c @top_srcdir@/src/graph.c

grid_graph_test_CFLAGS = $(DEPS_CFLAGS)
grid_graph_test_LDADD  = $(DEPS_LIBS)
grid_graph_test_SOURCES = ../graph/grid_graph_test.c @top_srcdir@/src/graph.c

uniform_tree_test_CFLAGS = $(DEPS_CFLAGS)
uniform_tree_test_LDADD  = $(DEPS_LIBS)
uniform_tree_test_SOURCES = ../graph/uniform_tree_test.c @top_srcdir@/src/graph.c

game_payoff_test_CFLAGS = $(DEPS_CFLAGS)
game_payoff_test_LDADD  = $(DEPS_LIBS)
game_payoff_test_SOURCES = ../game/game_payoff_test.c @top_srcdir@/src/graph.c @top_srcdir@/src/game.c @top_srcdir@/src/random.c

game_p_i_test_CFLAGS = $(DEPS_CFLAGS)
game_p_i_test_LDADD  = $(DEPS_LIBS)
game_p_i_test_SOURCES = ../game/game_p_i_test.c @top_srcdir@/src/graph.c @top_srcdir@/src/game.c @top_srcdir@/src/random.c

game_p_ij_test_CFLAGS = $(DEPS_CFLAGS)
game_p_ij_test_LDADD  = $(DEPS_LIBS)
game_p_ij_test_SOURCES = ../game/game_p_ij_test.c @top_srcdir@/src/graph.c @top_srcdir@/src/game.c @top_srcdir@/src/random.c

