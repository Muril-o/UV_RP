package look.graph;

import look.telegram.Info;
import look.utils.Utils;
import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartUtilities;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.axis.NumberAxis;
import org.jfree.chart.axis.NumberTickUnit;
import org.jfree.chart.plot.PlotOrientation;
import org.jfree.chart.plot.XYPlot;
import org.jfree.data.xy.XYDataset;
import org.jfree.data.xy.XYSeries;
import org.jfree.data.xy.XYSeriesCollection;

import java.io.File;
import java.io.IOException;

public class Graph {
    public static File updateGraphFile() throws IOException {
        XYSeries xySeries = new XYSeries("Índice UV");
        for (int i = 0; i < Utils.getDataValues().length; i++) {
            Double d = Double.valueOf(Utils.getDataValues()[i]);
            xySeries.add(Double.valueOf(i), d);
        }
        XYDataset xyDataset = new XYSeriesCollection(xySeries);
        JFreeChart chart = ChartFactory.createXYAreaChart("Dose diária de radiação UV", "Hora do dia", "Índice UV", xyDataset, PlotOrientation.VERTICAL, false, true, false);
        chart.setAntiAlias(true);

        XYPlot plot = chart.getXYPlot();
        NumberAxis axis = (NumberAxis) plot.getDomainAxis();

        axis.setTickUnit(new NumberTickUnit(1.0));
        axis.setRange(0, 24);

        ChartUtilities.saveChartAsPNG(new File(Info.FILE_LATEST), chart, 600, 450);
        return new File(Info.FILE_LATEST);
    }
}
