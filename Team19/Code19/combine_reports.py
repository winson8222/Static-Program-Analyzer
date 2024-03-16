import os
from bs4 import BeautifulSoup

def combine_html_reports(report_dir):
    # Directory containing HTML files
    html_files = [f for f in os.listdir(report_dir) if f.endswith('.html')]

    combined_html = BeautifulSoup('<html><head><title>Combined Report</title></head><body></body></html>', 'html.parser')

    for filename in html_files:
        with open(os.path.join(report_dir, filename), 'r') as file:
            soup = BeautifulSoup(file, 'html.parser')
            body = soup.find('body')
            if body:
                combined_html.body.append(body)

    # Save the combined HTML
    combined_report_path = os.path.join(report_dir, 'combined_report.html')
    with open(combined_report_path, 'w') as file:
        file.write(str(combined_html))
    print(f"Combined HTML report saved to {combined_report_path}")

if __name__ == "__main__":
    # Get the directory from the script's location
    report_dir = os.getcwd()
    print(report_dir)
    combine_html_reports(report_dir)