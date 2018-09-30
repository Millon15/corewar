.comment    "For a good mood, just look up my intra"
.name       "Repeta"

live %-1
dest: ld %112, r2
ld %197, r3
fork %:glasses
st r3, 0
add r1, r1, r2
fork %:glasses
fork %:glasses
zjmp %-200
fork %:glasses
sti  r1,%:dest , %1
zjmp %:dest
sti  r1,%1,r14
glasses: live %1
st r1, :dest
zjmp %:glasses
