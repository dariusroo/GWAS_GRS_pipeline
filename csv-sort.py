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

data = csv.reader(open(csv_name),delimiter=",");

out_csv = csv.writer(open(csv_outname, "wb"), delimiter="\t")

sortedlist = sorted(data, key=itemgetter(0), reverse=False)

out_csv.writerows(sortedlist);
