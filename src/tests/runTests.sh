echo "Testing everything";
cd ./audit_unittest;
make clean;
make test;
./audit_unittest;

cd ..;
cd ./candidate_unittest;
make clean;
make test;
./candidate_unittest;

cd ..;
cd ./cpl_unittest;
make clean;
make test;
./cpl_unittest;

cd ..;
cd ./electable_unittest;
make clean;
make test;
./electable_unittest;

cd ..;
cd ./election_unittest;
make clean;
make test;
./election_unittest;

cd ..;
cd ./error_test;
make clean;
make test;
./error_test;

cd ..;
cd ./fileops_unittest;
make clean;
make test;
./fileops_unittest;

cd ..;
cd ./guiwindow_unittest;
make clean;
make test;
./guiwindow_unittest;

cd ..;
cd ./mpo_unittest;
make clean;
make test;
./mpo_unittest;

cd ..;
cd ./multifile_unittest;
make clean;
make test;
./multifile_unittest;

cd ..;
cd ./mv_unittest;
make clean;
make test;
./mv_unittest;

cd ..;
cd ./opl_unittest;
make clean;
make test;
./opl_unittest;

cd ..;
cd ./party_unittest;
make clean;
make test;
./party_unittest;

cd ..;
cd ./rawdata_unittest;
make clean;
make test;
./rawdata_unittest;

cd ..;
cd ./votingsystem_unittest;
make clean;
make test;
./votingsystem_unittest;

cd ..;
cd ./votingsystemfactory_unittest;
make clean;
make test;
./votingsystemfactory_unittest;

cd ..;
cd ./system_test;
make clean;
make test;
./system_test;

cd..;
echo "Done!";
