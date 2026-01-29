Import("env")

print("=== Adding CL42T.c to test build ===")

# Chemin vers ton fichier source
src_file = "src/2_DRV/CL42T/Src/CL42T.c"

# Compile CL42T.c en objet et ajoute-le aux tests
env.Prepend(TEST_BUILD_SRC=[src_file])

print("=== CL42T.c added to test build ===")
