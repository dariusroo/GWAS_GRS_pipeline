import csv
import sys
import argparse
from operator import itemgetter

parser = argparse.ArgumentParser();

parser.add_argument("--input", "-i", dest="input_file", type=str, required=True);
parser.add_argument("--output", "-o", dest="output_file", type=str, required=True);

args = parser.parse_args();

txt_file = args.input_file;
csv_file = args.output_file;

in_txt = csv.reader(open(txt_file, "rb"), delimiter = "\t");
out_csv = csv.writer(open(csv_file, "wb"));

out_csv.writerows(in_txt);
