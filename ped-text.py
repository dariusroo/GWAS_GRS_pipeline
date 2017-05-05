import csv
import sys
import argparse
from operator import itemgetter

parser = argparse.ArgumentParser();

parser.add_argument("--input", "-i", dest="input_file", type=str, required=True);
parser.add_argument("--output", "-o", dest="output_file", type=str, required=True);

args = parser.parse_args();

csv_name = args.input_file;
csv_outname = args.output_file;

f = open(csv_name, "rb");
cw = csv.writer(open(csv_outname, "wb"), delimiter=' ', quoting=csv.QUOTE_NONE, escapechar='|');

with f as inf:
	for line in inf:
		parts = line.split();
		cw.writerow(parts[6:]);
