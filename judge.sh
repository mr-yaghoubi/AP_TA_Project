#!/bin/bash

GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m' 

OUTPUT=DadeNegar
TESTS=tests

TIME_LIMIT=10


total_cnt=0
passed_cnt=0
failed_cnt=0

if [ ! -f "./${OUTPUT}" ]; then
    echo -e "${RED}Executable ${OUTPUT} not found!${NC}"
    exit 1
fi


for test_folder in ${TESTS}/*; do

    if [ -d ${test_folder} ]; then
        total_cnt=$((total_cnt+1))
        test_name=$(basename ${test_folder})
        input_file=${test_folder}/*.in
        expected_output_file=${test_folder}/*.out
        code_output_file="$test_folder/$test_name.temp"
        error_file="$test_folder/error_log.err"

        timeout ${TIME_LIMIT} ./${OUTPUT} < ${input_file} > ${code_output_file}
        if [ $? -ne 0 ]; then
            failed_cnt=$((failed_cnt+1))
            echo -e "${RED}Test named $test_name failed. This could be due to timeout.${NC}"
        else
            if diff -q --ignore-trailing-space ${code_output_file} ${expected_output_file} > /dev/null; then
                passed_cnt=$((passed_cnt+1))
                echo -e "${GREEN}Test named $test_name passed${NC}"
                rm ${code_output_file}
                if [ -f ${error_file} ]; then
                    rm ${error_file}
                fi
            else
                diff -y --ignore-trailing-space ${code_output_file} ${expected_output_file} > ${error_file}
                failed_cnt=$((failed_cnt+1))
                echo -e "${RED}Test named $test_name failed${NC}"
            fi

        fi

    fi

done


echo -e "${YELLOW}------------------------${NC}"
echo -e "${YELLOW}Test summary:${NC}"
echo -e "${GREEN}Passed: $passed_cnt${NC}"
echo -e "${RED}Failed: $failed_cnt${NC}"
echo -e "${YELLOW}Total: $total_cnt${NC}"
